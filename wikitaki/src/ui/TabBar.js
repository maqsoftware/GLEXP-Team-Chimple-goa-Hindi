chimple.TabBar = chimple.ScrollableButtonPanel.extend({
    ctor:function(position, size, numButtonsPerScreen, menuDef, callBackFunction, callBackContext) {
        this._super(position, size, numButtonsPerScreen, 1, menuDef, callBackFunction, callBackContext, true);
        if(this._buttonPanel) {
            this._buttonPanel.setBackGroundColor(cc.color.RED);                        
        }
    }
}); 