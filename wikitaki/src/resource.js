var chimple = chimple || {};

var defaultFolder = "";
var defaultMiscFolder = "/wp-content/themes/SocialChef/images/res/";

if (!cc.sys.isNative) {
    defaultFolder = "/wp-content/themes/SocialChef/images/res/";
}


var res = {
    HelloWorld_png : "/wp-content/themes/SocialChef/images/res/HelloWorld.png",
    add_png: "/wp-content/themes/SocialChef/images/res/icons/add.png",
    add_animation_png: "/wp-content/themes/SocialChef/images/res/icons/add_animation.png",
    add_animation_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_animation_onclick.png",
    add_audio_png: "/wp-content/themes/SocialChef/images/res/icons/add_audio.png",
    add_audio_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_audio_onclick.png",
    add_bg_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_bg-onclick.png",
    add_bg_png: "/wp-content/themes/SocialChef/images/res/icons/add_bg.png",
    add_char_png: "/wp-content/themes/SocialChef/images/res/icons/add_char.png",
    add_char_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_char_onclick.png",
    add_effects_png: "/wp-content/themes/SocialChef/images/res/icons/add_effects.png",
    add_effects_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_effects_onclick.png",
    add_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_onclick.png",
    add_qna_png: "/wp-content/themes/SocialChef/images/res/icons/add_qna.png",
    add_qna_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_qna_onclick.png",
    add_text_png: "/wp-content/themes/SocialChef/images/res/icons/add_text.png",
    add_text_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/add_text_onclick.png",
    animation_png: "/wp-content/themes/SocialChef/images/res/icons/animation.png",
    animation_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/animation_onclick.png",
    audio_png: "/wp-content/themes/SocialChef/images/res/icons/audio.png",
    audio_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/audio_onclick.png",
    back_png: "/wp-content/themes/SocialChef/images/res/icons/back.png",
    back_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/back_onclick.png",
    beard_png: "/wp-content/themes/SocialChef/images/res/icons/beard.png",
    beard_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/beard_onclick.png",
    book_png: "/wp-content/themes/SocialChef/images/res/icons/book.png",
    book_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/book_onclick.png",
    chimpleworld_png: "/wp-content/themes/SocialChef/images/res/icons/chimpleworld.png",
    chimpleworld_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/chimpleworld_onclick.png",
    coins_png: "/wp-content/themes/SocialChef/images/res/icons/coins.png",
    coins_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/coins_onclick.png",
    delete_png: "/wp-content/themes/SocialChef/images/res/icons/delete.png",
    delete_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/delete_onclick.png",
    edit_png: "/wp-content/themes/SocialChef/images/res/icons/edit.png",
    edit_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/edit_onclick.png",
    effects_png: "/wp-content/themes/SocialChef/images/res/icons/effects.png",
    effects_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/effects_onclick.png",
    emoticons_png: "/wp-content/themes/SocialChef/images/res/icons/emoticons.png",
    emoticons_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/emoticons_onclick.png",
    eyes_png: "/wp-content/themes/SocialChef/images/res/icons/eyes.png",
    eyes_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/eyes_onclick.png",
    flipx_png: "/wp-content/themes/SocialChef/images/res/icons/flipX.png",
    flipx_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/flipX_onclick.png",
    flipy_png: "/wp-content/themes/SocialChef/images/res/icons/flipY.png",
    flipy_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/flipY_onclick.png",
    game_png: "/wp-content/themes/SocialChef/images/res/icons/game.png",
    game_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/game_onclick.png",
    glass_png: "/wp-content/themes/SocialChef/images/res/icons/glass.png",
    glass_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/glass_onclick.png",
    hair_color_png: "/wp-content/themes/SocialChef/images/res/icons/hair_color.png",
    hair_color_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/hair_color_onclick.png",
    hairstyle_png: "/wp-content/themes/SocialChef/images/res/icons/hairstyle.png",
    hairstyle_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/hairstyle_onclick.png",
    hand_access_png: "/wp-content/themes/SocialChef/images/res/icons/hand_access.png",
    hand_access_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/hand_access_onclick.png",
    hat_png: "/wp-content/themes/SocialChef/images/res/icons/hat.png",
    hat_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/hat_onclick.png",
    head_shape_png: "/wp-content/themes/SocialChef/images/res/icons/head_shape.png",
    head_shape_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/head_shape_onclick.png",
    help_png: "/wp-content/themes/SocialChef/images/res/icons/help.png",
    help_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/help_onclick.png",
    home_png: "/wp-content/themes/SocialChef/images/res/icons/home.png",
    home_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/home_onclick.png",
    mat_que_png: "/wp-content/themes/SocialChef/images/res/icons/mat_que.png",
    mat_que_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/mat_que_onclick.png",
    mouth_png: "/wp-content/themes/SocialChef/images/res/icons/mouth.png",
    mouth_2_png: "/wp-content/themes/SocialChef/images/res/icons/mouth_2.png",
    mouth_2_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/mouth_2_onclick.png",
    mouth_access_png: "/wp-content/themes/SocialChef/images/res/icons/mouth_access.png",
    mouth_access_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/mouth_access_onclick.png",
    mouth_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/mouth_onclick.png",
    multi_que_png: "/wp-content/themes/SocialChef/images/res/icons/multi_que.png",
    multi_que_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/multi_que_onclick.png",
    my_avatar_png: "/wp-content/themes/SocialChef/images/res/icons/my_avatar.png",
    my_avatar_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/my_avatar_onclick.png",
    my_pet_png: "/wp-content/themes/SocialChef/images/res/icons/my_pet.png",
    my_pet_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/my_pet_onclick.png",
    neck_access_png: "/wp-content/themes/SocialChef/images/res/icons/neck_access.png",
    neck_access_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/neck_access_onclick.png",
    next_png: "/wp-content/themes/SocialChef/images/res/icons/next.png",
    next_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/next_onclick.png",
    pant_png: "/wp-content/themes/SocialChef/images/res/icons/pant.png",
    pant_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/pant_onclick.png",
    play_png: "/wp-content/themes/SocialChef/images/res/icons/play.png",
    play_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/play_onclick.png",
    props_png: "/wp-content/themes/SocialChef/images/res/icons/props.png",
    props_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/props_onclick.png",
    record_png: "/wp-content/themes/SocialChef/images/res/icons/record.png",
    record_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/record_onclick.png",
    rotate_png: "/wp-content/themes/SocialChef/images/res/icons/rotate.png",
    rotate_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/rotate_onclick.png",
    settings_png: "/wp-content/themes/SocialChef/images/res/icons/settings.png",
    settings_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/settings_onclick.png",
    shirt_png: "/wp-content/themes/SocialChef/images/res/icons/shirt.png",
    shirt_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/shirt_onclick.png",
    shoe_png: "/wp-content/themes/SocialChef/images/res/icons/shoe.png",
    shoe_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/shoe_onclick.png",
    skintone_png: "/wp-content/themes/SocialChef/images/res/icons/skintone.png",
    skintone_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/skintone_onclick.png",
    stop_png: "/wp-content/themes/SocialChef/images/res/icons/stop.png",
    stop_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/stop_onclick.png",
    stop_recording_png: "/wp-content/themes/SocialChef/images/res/icons/stop_recording.png",
    stop_recording_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/stop_recording_onclick.png",
    translate_png: "/wp-content/themes/SocialChef/images/res/icons/translate.png",
    translate_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/translate_onclick.png",
    text_png: "/wp-content/themes/SocialChef/images/res/icons/text.png",
    text_onclick_png: "/wp-content/themes/SocialChef/images/res/icons/text_onclick.png",
    cowboy_body_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_body.png",
    cowboy_eye_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_eye.png",
    cowboy_face_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_face.png",
    cowboy_hat_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_hat.png",
    cowboy_left_hand_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_left_hand.png",
    cowboy_left_leg_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_left_leg.png",
    cowboy_mouth_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_mouth.png",
    cowboy_right_hand_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_right_hand.png",
    cowboy_right_leg_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_right_leg.png",
    cowboy_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/human/cowboy_thumbnail.png",    
    human_json: "/wp-content/themes/SocialChef/images/res/characters/human/human.json",
    face_png: "/wp-content/themes/SocialChef/images/res/characters/human/face.png",
    hair_png: "/wp-content/themes/SocialChef/images/res/characters/human/hair.png",
    left_eye_png: "/wp-content/themes/SocialChef/images/res/characters/human/left_eye.png",
    left_hand_png: "/wp-content/themes/SocialChef/images/res/characters/human/left_hand.png",
    right_eye_png: "/wp-content/themes/SocialChef/images/res/characters/human/right_eye.png",
    right_hand_png: "/wp-content/themes/SocialChef/images/res/characters/human/right_hand.png",
    right_leg_png: "/wp-content/themes/SocialChef/images/res/characters/human/right_leg.png",
    Left_leg_png: "/wp-content/themes/SocialChef/images/res/characters/human/Left_leg.png",
    body_png: "/wp-content/themes/SocialChef/images/res/characters/human/body.png",
    cricketer_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/human/cricketer_thumbnail.png",
    Animation_json: "/wp-content/themes/SocialChef/images/res/characters/crow/Animation.json",
    Beak_Lower_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Beak_Lower.png",
    Beak_Upper_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Beak_Upper.png",
    Body_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Body.png",
    Eye_Inner_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Eye_Inner.png",
    Eye_Outer_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Eye_Outer.png",
    Leg_back_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Leg_back.png",
    Leg_front_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Leg_front.png",
    Tail_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Tail.png",
    Wings_png: "/wp-content/themes/SocialChef/images/res/characters/crow/Wings.png",
    crow_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/crow/crow_thumbnail.png",
    donkey_Skeleton_json: "/wp-content/themes/SocialChef/images/res/characters/donkey/Skeleton.json",
    body_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/body donkey.png",
    donkey_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/donkey_thumbnail.png",
    head_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/head donkey.png",
    leg_down_2_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/leg down 2 donkey.png",
    leg_down_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/leg down donkey.png",
    leg_up_2_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/leg up 2 donkey.png",
    leg_up_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/leg up donkey.png",
    tail_donkey_png: "/wp-content/themes/SocialChef/images/res/characters/donkey/tail donkey.png",
    ele_02_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-02.png",
    ele_03_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-03.png",
    ele_04_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-04.png",
    ele_05_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-05.png",
    ele_06_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-06.png",
    ele_07_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-07.png",
    ele_08_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-08.png",
    ele_09_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-09.png",
    ele_10_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/ele-10.png",
    elep_json: "/wp-content/themes/SocialChef/images/res/characters/elephant/elep.json",
    elephant_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/elephant/elephant_thumbnail.png",
    Skeleton_json: "/wp-content/themes/SocialChef/images/res/characters/hare/Skeleton.json",
    hare_body_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_body.png",
    hare_eyes_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_eyes.png",
    hare_head_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_head.png",
    hare_leftear_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_leftear.png",
    hare_lefthand_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_lefthand.png",
    hare_rightear_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_rightear.png",
    hare_righthand_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_righthand.png",
    hare_rightleg_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_rightleg.png",
    hare_thumbnail_png: "/wp-content/themes/SocialChef/images/res/characters/hare/hare_thumbnail.png",
    close_pop_png: "/wp-content/themes/SocialChef/images/res/close_pop.png",
    boy_json: "/wp-content/themes/SocialChef/images/res/Animation.json",
    skeleton_config_boy_skeleton_json: "/wp-content/themes/SocialChef/images/res/characters/skeletonConfig/BoySkeleton.json",
    skeleton_config_cowboy_skeleton_json: "/wp-content/themes/SocialChef/images/res/characters/skeletonConfig/CowboySkeleton.json",
    boy_animation_json: "/wp-content/themes/SocialChef/images/res/boy_animation.json",
    sliderProgess_png: "/wp-content/themes/SocialChef/images/res/sliderProgress.png",
    sliderThumb_png: "/wp-content/themes/SocialChef/images/res/sliderThumb.png",
    sliderTrack_png: "/wp-content/themes/SocialChef/images/res/sliderTrack.png",
    textBubble_png: "/wp-content/themes/SocialChef/images/res/ninepatch_bubble_300x300.png",
    bubble_png: "/wp-content/themes/SocialChef/images/res/bubble.png",
    textTemplate_json: "/wp-content/themes/SocialChef/images/res/TextScene.json"  
};


var misc = {
    Config_json: defaultMiscFolder + "misc/storyConfig.json"
};


var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
};



cc.loader.loadJson(misc.Config_json, function (error, data) {
    chimple.storyConfigurationObject = data;

    Object.getOwnPropertyNames(chimple.storyConfigurationObject).forEach(function (element) {
        cc.log("processing:" + element);
        var configObj = chimple.storyConfigurationObject[element];
        // if (configObj != null) {
        //     cc.log('configObj.icon:' + configObj.icon);
        //     cc.log('configObj.cIcon:' + configObj.cIcon);
        //     if(configObj.categories) {
        //         configObj.categories.forEach(function (eleObj) {
        //             cc.log('eleObj.icon:' + eleObj.icon);
        //             cc.log('eleObj.cIcon:' + eleObj.cIcon);

        //             eleObj.items.forEach(function(itmObj) {
        //                 console.log('itmObj.json:' + itmObj.itmObj);
        //                 cc.log('itmObj.icon:' + itmObj.icon);
        //                 cc.log('itmObj.cIcon:' + itmObj.cIcon);

        //             }, this);
        //         }, this);

        //     }
        // }
    }, this);
});