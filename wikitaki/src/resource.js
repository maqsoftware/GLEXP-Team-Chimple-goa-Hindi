var chimple = chimple || {};

var defaultFolder = "";
var defaultMiscFolder = "/wp-content/themes/SocialChef/images/res/";

if (!cc.sys.isNative) {
    defaultFolder = "/wp-content/themes/SocialChef/images/res/";
}


var res = {
    icons1_png: "/wp-content/themes/SocialChef/images/res/icons1.png",
    icons1_plist: "/wp-content/themes/SocialChef/images/res/icons1.plist",
    icons2_png: "/wp-content/themes/SocialChef/images/res/icons2.png",
    icons2_plist: "/wp-content/themes/SocialChef/images/res/icons2.plist",
    HelloWorld_png : "/wp-content/themes/SocialChef/images/res/HelloWorld.png",
    crow_json: "/wp-content/themes/SocialChef/images/res/characters/crow/Animation.json",
    elephant_json: "/wp-content/themes/SocialChef/images/res/characters/elephant/elep.json",
    donkey_skeleton_json: "/wp-content/themes/SocialChef/images/res/characters/donkey/Skeleton.json",
    human_skeleton_json: "/wp-content/themes/SocialChef/images/res/human_skeleton.json",
    textBubble_png: "/wp-content/themes/SocialChef/images/res/ninepatch_bubble_300x300.png",
    bubble_png: "/wp-content/themes/SocialChef/images/res/bubble.png",
    textTemplate_json: "/wp-content/themes/SocialChef/images/res/TextScene.json"  
};


var misc = {
    Config_json: defaultMiscFolder + "misc/storyConfig.json",
    EditPlayConfig_json: defaultMiscFolder + "misc/playConfig.json",
    OnlyStoryPlayConfig_json: defaultMiscFolder + "misc/onlyPlayConfig.json",
    
};


var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
};


cc.loader.loadJson(misc.EditPlayConfig_json, function (error, data) {
    chimple.storyPlayConfigurationObject = data;
});

cc.loader.loadJson(misc.OnlyStoryPlayConfig_json, function (error, data) {
    chimple.onlyStoryPlayConfigurationObject = data;
});


cc.loader.loadJson(misc.Config_json, function (error, data) {
    chimple.storyConfigurationObject = data;
});