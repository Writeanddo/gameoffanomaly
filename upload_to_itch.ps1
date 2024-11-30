﻿$BUTLER_PATH = "$ENV:AppData\itch\apps\butler\butler.exe"
$VERSION = git log -1 --format="%h"

$ITCH_USER = "enweave"
$ITCH_GAME = "anomaly"
$ITCH_CHANNEL = "windows"
$BUILD_DIR = "build/Windows"

echo "uploading to itch.io"

$butlerStartParams = @{
    FilePath     = $BUTLER_PATH
    ArgumentList = "push", $BUILD_DIR, "$ITCH_USER/$ITCH_GAME`:$ITCH_CHANNEL", "--userversion", $VERSION
    Wait         = $true
    PassThru     = $true
}
$proc = Start-Process @butlerStartParams
$proc.ExitCode

echo "Uploading done"