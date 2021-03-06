/*
 * Copyright 2017, Team Chimple
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.maq.xprize.bali.repo;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;
import android.content.ContentValues;
import android.content.Context;
import android.os.AsyncTask;

import com.maq.xprize.bali.db.AppDatabase;
import com.maq.xprize.bali.db.entity.Lesson;
import com.maq.xprize.bali.db.entity.Unit;
import com.maq.xprize.bali.db.entity.User;
import com.maq.xprize.bali.db.entity.UserLesson;
import com.maq.xprize.bali.db.entity.UserLog;
import com.maq.xprize.bali.db.pojo.EagerUnitPart;
import com.maq.xprize.bali.db.pojo.FlashCard;
import com.maq.xprize.bali.model.BagOfChoiceQuiz;
import com.maq.xprize.bali.model.MultipleChoiceQuiz;
import com.maq.simpleclass.R;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ThreadLocalRandom;

import static com.maq.xprize.bali.provider.LessonContentProvider.COINS;
import static com.maq.xprize.bali.provider.LessonContentProvider.GAME_EVENT;
import static com.maq.xprize.bali.provider.LessonContentProvider.GAME_LEVEL;
import static com.maq.xprize.bali.provider.LessonContentProvider.GAME_NAME;
import static com.maq.xprize.bali.provider.LessonContentProvider.URI_COIN;

public class LessonRepo {
    public static final int ANY_FORMAT = 0;

    public static final int UPPER_CASE_LETTER_FORMAT = 1;

    private static final MutableLiveData ABSENT = new MutableLiveData();

    {
        //noinspection unchecked
        ABSENT.setValue(null);
    }

    public static void markNextLesson(Context context, final long lessonId) {
        new AsyncTask<Context, Void, Void>() {
            @Override
            protected Void doInBackground(Context... params) {
                Context context1 = params[0];
                AppDatabase db = AppDatabase.getInstance(context1);
                User user = UserRepo.getCurrentUser(context1);
                //TODO: Handle no user
                Lesson lesson;
                if (lessonId != 0) {
                    lesson = db.lessonDao().getLessonById(lessonId);
                } else {
                    lesson = db.lessonDao().getLessonById(user.currentLessonId);
                }
                Lesson newLesson = db.lessonDao().getLessonBySeq(lesson.seq + 1);
                if (newLesson != null) {
                    user.currentLessonId = newLesson.id;
                    db.userDao().updateUser(user);
                }
                return null;
            }
        }.execute(context);
    }

    public static LiveData<Integer> rewardCoins(final Context context, final long lessonId, final int percent) {
        final MutableLiveData<Integer> coinLiveData = ABSENT;
        new AsyncTask<Void, Void, Void>() {
            @Override
            protected Void doInBackground(Void... voids) {
                AppDatabase db = AppDatabase.getInstance(context);
                User user = UserRepo.getCurrentUser(context);
                //TODO: Handle no user
                Lesson lesson;
                if (lessonId != 0) {
                    lesson = db.lessonDao().getLessonById(lessonId);
                } else {
                    lesson = db.lessonDao().getLessonById(user.currentLessonId);
                }
                UserLesson userLesson = db.userLessonDao().getUserLessonByUserIdAndLessonId(user.id, lesson.id);
                if (userLesson == null) {
                    userLesson = new UserLesson(user.id, lesson.id, new Date(), 1, percent);
                    db.userLessonDao().insertUserLesson(userLesson);
                } else {
                    userLesson.seenCount++;
                    userLesson.lastSeenAt = new Date();
                    db.userLessonDao().updateUserLesson(userLesson);
                }
//                if(percent >= 65 && userLesson.seenCount >= 3) {
                if (percent >= 0 && userLesson.seenCount >= 1) {
                    Lesson newLesson = db.lessonDao().getLessonBySeq(lesson.seq + 1);
                    if (newLesson != null) {
                        user.currentLessonId = newLesson.id;
                        db.userDao().updateUser(user);
                    }
                }
                int coinsToGive = 0;
                if (percent >= 80)
                    coinsToGive = 4;
                else if (percent >= 60)
                    coinsToGive = 3;
                else if (percent >= 40)
                    coinsToGive = 2;
                else if (percent >= 20)
                    coinsToGive = 1;
                ContentValues contentValues = new ContentValues(1);
                contentValues.put(GAME_NAME, "Bali");
                contentValues.put(GAME_LEVEL, lesson.seq);
                contentValues.put(GAME_EVENT, UserLog.STOP_EVENT);
                contentValues.put(COINS, coinsToGive);
                int coins = context.getContentResolver().update(
                        URI_COIN,
                        contentValues,
                        null,
                        null
                );

                coinLiveData.postValue(coinsToGive);
                return null;
            }
        }.execute();
        return coinLiveData;
    }

    public static List<MultipleChoiceQuiz> getMultipleChoiceQuizes(Context context, int numQuizes
            , int numChoices, int answerFormat, int choiceFormat) {
        AppDatabase db = AppDatabase.getInstance(context);
        User user = UserRepo.getCurrentUser(context);
        Lesson currentLesson = db.lessonDao().getLessonById(user.currentLessonId);
        int concept = currentLesson.concept;
        List<FlashCard> lucs;
        boolean answerCaseParticular = (answerFormat == UPPER_CASE_LETTER_FORMAT);
        if ((answerFormat == ANY_FORMAT
                || (answerFormat == UPPER_CASE_LETTER_FORMAT
                && (currentLesson.concept == Lesson.LETTER_CONCEPT
                || currentLesson.concept == Lesson.UPPER_CASE_TO_LOWER_CASE_CONCEPT
                || currentLesson.concept == Lesson.LETTER_TO_WORD_CONCEPT
                || currentLesson.concept == Lesson.UPPER_CASE_LETTER_TO_WORD_CONCEPT)))
                && (choiceFormat == ANY_FORMAT
                || (choiceFormat == UPPER_CASE_LETTER_FORMAT
                && (currentLesson.concept == Lesson.LETTER_CONCEPT
                || currentLesson.concept == Lesson.UPPER_CASE_TO_LOWER_CASE_CONCEPT)))) {
            lucs = db.lessonUnitDao().getFlashCardsByLessonId(currentLesson.id);
            convertToUniqueSubjects(lucs, answerCaseParticular);
            if (lucs.size() < numQuizes) {
                lucs = db.lessonUnitDao().getFlashCardArrayBelowSeqAndByConcept(currentLesson.seq, currentLesson.concept);
                convertToUniqueSubjects(lucs, answerCaseParticular);
            }
        } else {
            List<Integer> formats = new LinkedList<>();
            formats.add(Lesson.LETTER_CONCEPT);
            formats.add(Lesson.UPPER_CASE_TO_LOWER_CASE_CONCEPT);
            if (choiceFormat == ANY_FORMAT) {
                formats.add(Lesson.LETTER_TO_WORD_CONCEPT);
                formats.add(Lesson.UPPER_CASE_LETTER_TO_WORD_CONCEPT);
            }
            Lesson[] lessons = db.lessonDao().getLessonsBelowSeqAndByConcept(currentLesson.seq, formats);
            int lessonIndex = 0;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
                lessonIndex = ThreadLocalRandom.current().nextInt(lessons.length);
            }
            lucs = db.lessonUnitDao().getFlashCardsByLessonId(lessons[lessonIndex].id);
            concept = lessons[lessonIndex].concept;
            convertToUniqueSubjects(lucs, answerCaseParticular);
            if (lucs.size() < numQuizes) {
                lucs = db.lessonUnitDao().getFlashCardArrayBelowSeqAndByConcept(currentLesson.seq, concept);
                convertToUniqueSubjects(lucs, answerCaseParticular);
            }

        }
        List<MultipleChoiceQuiz> mcqs = new ArrayList<>(numQuizes);

        ArrayList<Integer> quizList = new ArrayList<>();
        for (int i = 0; i < lucs.size(); i++) {
            quizList.add(i);
        }
        Collections.shuffle(quizList);

        for (int i = 0; i < numQuizes; i++) {
            int lucIndex = quizList.get(Math.min(i, quizList.size() - 1));
            FlashCard luc = lucs.get(lucIndex);
            Unit[] choices = new Unit[numChoices];

            ArrayList<Integer> choiceList = new ArrayList<>();
            for (int j = 0; j < lucs.size(); j++) {
                if (!luc.subjectUnit.name.equals(lucs.get(j).subjectUnit.name)) {
                    choiceList.add(j);
                }
            }
            Collections.shuffle(choiceList);

            int answerIndex = 0;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
                answerIndex = ThreadLocalRandom.current().nextInt(numChoices);
            }
            for (int c = 0; c < numChoices; c++) {
                if (c == answerIndex) {
                    choices[c] = luc.objectUnit;
                } else {
                    int randIndex = choiceList.get(Math.min(c, choiceList.size() - 1));
                    choices[c] = lucs.get(randIndex).objectUnit;
                }
            }
            Unit answer = luc.subjectUnit;
            if (answerFormat == UPPER_CASE_LETTER_FORMAT) {
                answer.name = answer.name.toUpperCase(Locale.getDefault());
            }
            if (choiceFormat == UPPER_CASE_LETTER_FORMAT) {
                for (Unit choice : choices) {
                    //TODO: Handle unicode
                    choice.name = choice.name.substring(0, 1).toUpperCase(Locale.getDefault());
                }
            }
            if (concept == Lesson.UPPER_CASE_LETTER_TO_WORD_CONCEPT) {
                for (Unit choice : choices) {
                    //TODO: Handle unicode
                    choice.name = choice.name.substring(0, 1).toUpperCase(Locale.getDefault()) + choice.name.substring(1);
                }
            }
            MultipleChoiceQuiz mcq = new MultipleChoiceQuiz(context.getResources().getString(R.string.word),
                    answer, choices, answerIndex);
            mcqs.add(mcq);
        }
        return mcqs;
    }

    private static void convertToUniqueSubjects(List<FlashCard> lucs, boolean caseInvariant) {
        Set<String> subjectSet = new HashSet<>(lucs.size());
        for (Iterator<FlashCard> iter = lucs.iterator(); iter.hasNext(); ) {
            FlashCard luc = iter.next();
            String compareStr = luc.subjectUnit.name;
            if (caseInvariant) {
                compareStr = compareStr.toUpperCase(Locale.getDefault());
            }
            if (!subjectSet.contains(compareStr)) {
                subjectSet.add(compareStr);
            } else {
                iter.remove();
            }
        }
    }

    public static List<BagOfChoiceQuiz> getBagOfChoiceQuizes(Context context, int numQuizes
            , int minAnswers, int maxAnswers, int minChoices, int maxChoices, boolean order) {
        //TODO: for now assume order is true
        AppDatabase db = AppDatabase.getInstance(context);
        User user = UserRepo.getCurrentUser(context);
        Lesson lesson = db.lessonDao().getLessonById(user.currentLessonId);
        FlashCard[] lucs = db.lessonUnitDao().getFlashCardArrayByLessonId(lesson.id);

        List<BagOfChoiceQuiz> bcqs = new ArrayList<>(numQuizes);

        if (lesson.concept == Lesson.LETTER_TO_WORD_CONCEPT) {
            ArrayList<Integer> quizList = new ArrayList<>();
            Set<String> choiceSet = new HashSet<>(lucs.length);
            Map<String, String[]> wordMap = new HashMap<>(lucs.length);
            fillChoicesWithWords(minAnswers, maxAnswers, lucs, quizList, choiceSet, wordMap);
            if (quizList.size() == 0) {
                fillChoicesWithWords(minAnswers, maxChoices, lucs, quizList, choiceSet, wordMap);
            }
            if (quizList.size() == 0) {
                fillChoicesWithWords(minChoices, maxChoices, lucs, quizList, choiceSet, wordMap);
            }
            Collections.shuffle(quizList);

            for (int i = 0; i < numQuizes; i++) {
                int lucIndex = quizList.get(Math.min(i, quizList.size() - 1));
                FlashCard luc = lucs[lucIndex];
                String answer = luc.objectUnit.name;
                String[] answers = wordMap.get(answer);
                Set<String> choiceCloneSet = new HashSet<>(choiceSet);
                for (String answerA : answers) {
                    choiceCloneSet.remove(answerA);
                }
                List<String> choiceList = new LinkedList<>(choiceCloneSet);
                Collections.shuffle(choiceList);

                String[] choices = new String[maxChoices - answers.length];
                for (int c = 0; c < choices.length; c++) {
                    choices[c] = choiceList.get(Math.min(c, choiceList.size() - 1));
                }

                BagOfChoiceQuiz bcq = new BagOfChoiceQuiz(context.getResources().getString(R.string.word)
                        , answer
                        , answers
                        , choices);

                bcqs.add(bcq);
            }
        } else if (lesson.concept == Lesson.SYLLABLE_TO_WORD_CONCEPT) {
            ArrayList<Integer> quizList = new ArrayList<>();
            Map<Unit, EagerUnitPart[]> unitMap = new HashMap<>(lucs.length);
            Set<String> choiceSet = new HashSet<>(lucs.length);
            fillChoicesWithSyllables(minAnswers, maxAnswers, db, lucs, quizList, unitMap, choiceSet);
            if (quizList.size() == 0) {
                fillChoicesWithSyllables(minAnswers, maxChoices, db, lucs, quizList, unitMap, choiceSet);
            }
            if (quizList.size() == 0) {
                fillChoicesWithSyllables(minChoices, maxChoices, db, lucs, quizList, unitMap, choiceSet);
            }
            Collections.shuffle(quizList);

            for (int i = 0; i < numQuizes; i++) {
                int lucIndex = quizList.get(Math.min(i, quizList.size() - 1));
                FlashCard luc = lucs[lucIndex];
                EagerUnitPart[] unitParts = unitMap.get(luc.objectUnit);
                String[] answers = unitParts != null ? new String[unitParts.length] : new String[0];
                Set<String> choiceCloneSet = new HashSet<>(choiceSet);
                for (int a = 0; a < (unitParts != null ? unitParts.length : 0); a++) {
                    answers[a] = unitParts[a].partUnit.name;
                    choiceCloneSet.remove(answers[a]);
                }
                List<String> choiceList = new LinkedList<>(choiceCloneSet);
                Collections.shuffle(choiceList);

                String[] choices = new String[maxChoices - answers.length];
                for (int c = 0; c < choices.length; c++) {
                    choices[c] = choiceList.get(Math.min(c, choiceList.size() - 1));
                }

                BagOfChoiceQuiz bcq = new BagOfChoiceQuiz(context.getResources().getString(R.string.word)
                        , luc.objectUnit.name
                        , answers
                        , choices);

                bcqs.add(bcq);
            }
        } else {
            ArrayList<Integer> quizList = new ArrayList<>();
            for (int i = 0; i < lucs.length; i++) {
                quizList.add(i);
            }
            Collections.shuffle(quizList);

            for (int i = 0; i < numQuizes; i++) {
                int lucIndex = quizList.get(Math.min(i, quizList.size() - 1));
                FlashCard luc = lucs[lucIndex];
                List<String> answers = new LinkedList<>();
                List<String> choices = new LinkedList<>();

                ArrayList<Integer> choiceList = new ArrayList<>();
                for (int j = 0; j < lucs.length; j++) {
                    if (!luc.subjectUnit.name.equals(lucs[j].subjectUnit.name)) {
                        choiceList.add(j);
                    }
                }
                Collections.shuffle(choiceList);

                for (int a = 0; a < maxAnswers; a++) {
                    answers.add(luc.subjectUnit.name);
                }

                for (int c = 0; c < maxChoices - maxAnswers; c++) {
                    int randIndex = choiceList.get(Math.min(c, choiceList.size() - 1));
                    choices.add(lucs[randIndex].subjectUnit.name);
                }

                BagOfChoiceQuiz bcq = new BagOfChoiceQuiz(context.getResources().getString(R.string.word)
                        , luc.subjectUnit.name
                        , answers.toArray(new String[0])
                        , choices.toArray(new String[0]));

                bcqs.add(bcq);
            }

        }
        return bcqs;
    }

    private static void fillChoicesWithSyllables(int minAnswers, int maxAnswers, AppDatabase db, FlashCard[] lucs, ArrayList<Integer> quizList, Map<Unit, EagerUnitPart[]> unitMap, Set<String> choiceSet) {
        for (int i = 0; i < lucs.length; i++) {
            EagerUnitPart[] unitParts = db.unitPartDao().getEagerUnitPartsByUnitIdAndType(
                    lucs[i].objectUnit.id, Unit.SYLLABLE_TYPE);
            for (EagerUnitPart unitPart : unitParts) {
                choiceSet.add(unitPart.partUnit.name);
            }
            if (unitParts.length >= minAnswers && unitParts.length <= maxAnswers) {
                quizList.add(i);
                unitMap.put(lucs[i].objectUnit, unitParts);
            }
        }
    }

    private static void fillChoicesWithWords(int minAnswers, int maxAnswers, FlashCard[] lucs, ArrayList<Integer> quizList, Set<String> choiceSet, Map<String, String[]> wordMap) {
        for (int i = 0; i < lucs.length; i++) {
            String word = lucs[i].objectUnit.name;
            String[] letters = new String[word.length()];
            for (int s = 0; s < word.length(); s++) {
                //TODO: handle unicode and code points
                String letter = word.substring(s, s + 1);
                choiceSet.add(letter);
                letters[s] = letter;
            }
            if (word.length() >= minAnswers && word.length() <= maxAnswers) {
                quizList.add(i);
                wordMap.put(word, letters);
            }
        }
    }

}
