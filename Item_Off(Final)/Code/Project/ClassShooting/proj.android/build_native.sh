APPNAME="ClassShooting"
ENGINE_ROOT="/cygdrive/c/GameEngine"
NDK_ROOT="/cygdrive/c/GameEngine/ndk"
APP_ANDROID_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$APP_ANDROID_ROOT/.."

PATH=$PATH:$NDK_ROOT

for file in "$APP_ROOT"/Classes/*.cpp
do
    if [ -f "$file" ]; then
        FILENAME="../../Classes/"${file##*/}
        FILELIST=$FILELIST" $FILENAME"
    fi
done


if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

for file in "$APP_ROOT"/Resources/*
do
    if [ -d "$file" ]; then
        cp -rf "$file" "$APP_ANDROID_ROOT"/assets
    fi

    if [ -f "$file" ]; then
        cp "$file" "$APP_ANDROID_ROOT"/assets
    fi
done

file="$APP_ANDROID_ROOT"/assets/Icon-72.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-hdpi/icon.png
fi
file="$APP_ANDROID_ROOT"/assets/Icon-48.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-mdpi/icon.png
fi
file="$APP_ANDROID_ROOT"/assets/Icon-32.png
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/res/drawable-ldpi/icon.png
fi

"$NDK_ROOT"/ndk-build -C "$APP_ANDROID_ROOT" $* "NDK_MODULE_PATH=${ENGINE_ROOT}/cocos2d-2.0-x-2.0.4:${ENGINE_ROOT}/cocos2d-2.0-x-2.0.4/cocos2dx/platform/third_party/android/prebuilt"
