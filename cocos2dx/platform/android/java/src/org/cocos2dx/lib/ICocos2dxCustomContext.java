package org.cocos2dx.lib;

public interface ICocos2dxCustomContext {
    // event id
    public final static int EVENT_ID_MOVIE_MAKER = 1;
    
    // action id
    public final static int ACTION_ID_EMAIL = 1;
    public final static int ACTION_ID_GENERATE_VIDEO_TO_NOTEBOOK = 2;
    
    // context id
    public final static int CONTEXT_ID_NOTEBOOK = 1;
    public final static int CONTEXT_ID_LOADING_DLG = 2;
    
    public void callbackActivityOrViewController(int contextId);
    public void callbackPerformActionWithFilePath(int eventId, int actionId, String folderPath);
    public void callbackPerformActionWithFolderPath(int eventId, int actionId, String folderPath);
    public String callbackJsonEvent(String callbackJson);
}
