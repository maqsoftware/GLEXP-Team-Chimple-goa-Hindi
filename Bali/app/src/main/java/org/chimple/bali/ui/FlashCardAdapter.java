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

package org.chimple.bali.ui;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

import org.chimple.bali.db.pojo.FlashCard;
import org.chimple.bali.widget.LetterView;

import java.util.List;

public class FlashCardAdapter extends BaseAdapter {
    private final Context mContext;
    private List<FlashCard> mFlashCards;

    public FlashCardAdapter(Context context) {
        mContext = context;
    }

    public FlashCardAdapter(Context context, List<FlashCard> flashCards) {
        mContext = context;
        mFlashCards = flashCards;
    }

    public void setFlashCards(List<FlashCard> flashCards) {
        mFlashCards = flashCards;
        notifyDataSetChanged();
    }

    @Override
    public int getCount() {
        return mFlashCards.size();
    }

    @Override
    public Object getItem(int i) {
        return mFlashCards.get(i);
    }

    @Override
    public long getItemId(int i) {
        return mFlashCards.get(i).lessonUnit.seq;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        LetterView letterView = new LetterView(mContext);
        letterView.setLetter(mFlashCards.get(i).objectUnit.name);
        return letterView;
    }
}
