package com.mousebird.maply;

/**
 * The sticker manager interfaces to the Maply C++/JNI side of things
 * and is invisible to the toolkit users.
 */
public class StickerManager
{
    private StickerManager()
    {}

    StickerManager(Scene scene) { initialise(scene); }

    protected void finalize() { dispose(); }

    // Only supporting texture changes at the moment
    public void changeSticker(long stickerID,StickerInfo stickerInfo,ChangeSet changes)
    {
        modifyChunkTextures(stickerID,stickerInfo,changes);
        if (stickerInfo.getDrawPriority() != -1)
            modifyDrawPriority(stickerID,stickerInfo.getDrawPriority(),changes);
    }

    // Add a single sticker to the scene and return an ID for tracker
    public native long addStickers(Sticker[] stickers,StickerInfo stickerInfo,ChangeSet changes);

    // Modify the given chunk with new texture IDs
    public native boolean modifyChunkTextures(long stickerID,StickerInfo stickerInfo,ChangeSet changes);

    // Modify the draw priority
    public native boolean modifyDrawPriority(long stickerID,int drawPriority,ChangeSet changes);

    // Enable/disable stickers by ID
    public native void enableStickers(long[] ids, boolean enable, ChangeSet changes);

    // Remove stickers by ID
    public native void removeStickers(long[] ids, ChangeSet changes);

    static
    {
        nativeInit();
    }
    private static native void nativeInit();
    native void initialise(Scene scene);
    native void dispose();
    private long nativeHandle;
    private long nativeSceneHandle;
}
