chimple.PreviewPanel = cc.LayerColor.extend({
    ctor: function (width, height, position, target, configuration, callback, callbackContext) {
        this._super(cc.color.WHITE, width, height);
        var backButton = new ccui.Button(res.back_png, res.back_onclick_png);
        backButton.setPosition(0, height - 256);
        backButton.addTouchEventListener(this.goBack, this);
        this.addChild(backButton);
        
        this._target = target;
        this._targetParent = target.parent;
        this._targetPosition = target.getPosition();
        this._targetScale = target.getScale();
        target.removeFromParent(false);
        cc.eventManager.removeListeners(target);
        this.addChild(target);
        target.setPosition(0, 0);
        
        this.addChild(new chimple.TabPanel(cc.p(width / 3, 0), cc.size(width * 2 / 3, height), 2, 2, configuration, callback, callbackContext));       
    },
    goBack: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_ENDED:
                this.removeChild(this._target, false);
                this._targetParent.addChild(this._target);
                this._target.setPosition(this._targetPosition);
                this._target.setScale(this._targetScale);
                this._targetParent.registerEventListenerForChild(this._target);

                this.parent.removeChild(this, true);
                
                
                break;
        }
    },

});
