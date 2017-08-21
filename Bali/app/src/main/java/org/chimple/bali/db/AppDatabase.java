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

package org.chimple.bali.db;

import android.arch.persistence.room.Database;
import android.arch.persistence.room.Room;
import android.arch.persistence.room.RoomDatabase;
import android.arch.persistence.room.TypeConverters;
import android.content.Context;
import android.support.annotation.VisibleForTesting;

import org.chimple.bali.db.converter.DateConverter;
import org.chimple.bali.db.dao.LessonDao;
import org.chimple.bali.db.dao.LessonUnitDao;
import org.chimple.bali.db.dao.UnitDao;
import org.chimple.bali.db.dao.UnitPartDao;
import org.chimple.bali.db.dao.UserDao;
import org.chimple.bali.db.dao.UserLessonDao;
import org.chimple.bali.db.dao.UserUnitDao;
import org.chimple.bali.db.entity.Lesson;
import org.chimple.bali.db.entity.LessonUnit;
import org.chimple.bali.db.entity.Unit;
import org.chimple.bali.db.entity.UnitPart;
import org.chimple.bali.db.entity.User;
import org.chimple.bali.db.entity.UserLesson;
import org.chimple.bali.db.entity.UserUnit;

@Database(entities = {Lesson.class, LessonUnit.class, Unit.class, UnitPart.class,
        User.class, UserLesson.class, UserUnit.class},
        version = 1
)
@TypeConverters(DateConverter.class)
public abstract class AppDatabase extends RoomDatabase {
    public static final String DATABASE_NAME = "bali-db";

    /**
     * The only instance
     */
//    private static AppDatabase sInstance;

    public abstract LessonDao lessonDao();

    public abstract LessonUnitDao lessonUnitDao();

    public abstract UnitDao unitDao();

    public abstract UnitPartDao unitPartDao();

    public abstract UserDao userDao();

    public abstract UserLessonDao userLessonDao();

    public abstract UserUnitDao userUnitDao();

//    public static synchronized AppDatabase getInstance(Context context) {
//        if (sInstance == null) {
//            sInstance = Room
//                    .databaseBuilder(context.getApplicationContext(), AppDatabase.class, "bali_db")
//                    .build();
//            sInstance.populateInitialData();
//        }
//        return sInstance;
//    }
//
//    private void populateInitialData() {
//        if(lessonDao().count() == 0) {
//            Lesson lesson = new Lesson("vowels", 1, 1);
//            long lessonId = lessonDao().insertLesson(lesson);
//
//            Unit subjectUnit = new Unit("a", 1, "file://test/test.png", "file://test/test.mp3", "file://test/testp.mp3");
//            long subjectUnitId = unitDao().insertUnit(subjectUnit);
//
//            Unit objectUnit = new Unit("apple", 2, "file://test/apple.png", "file://test/apple.mp3", "file://test/applep.mp3");
//            long objectUnitId = unitDao().insertUnit(objectUnit);
//
//            LessonUnit lessonUnit = new LessonUnit(lessonId, 1, subjectUnitId, objectUnitId, "a");
//            lessonUnitDao().insertLessonUnit(lessonUnit);
//        }
//    }

//    /**
//     * Switches the internal implementation with an empty in-memory database.
//     *
//     * @param context The context.
//     */
//    @VisibleForTesting
//    public static void switchToInMemory(Context context) {
//        sInstance = Room.inMemoryDatabaseBuilder(context.getApplicationContext(),
//                AppDatabase.class).build();
//    }


}
