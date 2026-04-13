$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.Drawing

$root = Split-Path -Parent $PSScriptRoot
$textureDir = Join-Path $root "assets\textures"
$soundDir = Join-Path $root "assets\sounds"
$fontDir = Join-Path $root "assets\fonts"

New-Item -ItemType Directory -Force -Path $textureDir | Out-Null
New-Item -ItemType Directory -Force -Path $soundDir | Out-Null
New-Item -ItemType Directory -Force -Path $fontDir | Out-Null

Copy-Item "C:\Windows\Fonts\arial.ttf" (Join-Path $fontDir "arial.ttf") -Force

function New-Color([int]$r, [int]$g, [int]$b, [int]$a = 255) {
    return [System.Drawing.Color]::FromArgb($a, $r, $g, $b)
}

function Save-Bitmap([System.Drawing.Bitmap]$bitmap, [string]$path) {
    $bitmap.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
}

function New-Graphics([System.Drawing.Bitmap]$bitmap) {
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::None
    $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::NearestNeighbor
    $graphics.PixelOffsetMode = [System.Drawing.Drawing2D.PixelOffsetMode]::Half
    return $graphics
}

function Create-Background([string]$name, [System.Drawing.Color]$skyTop, [System.Drawing.Color]$skyBottom, [System.Drawing.Color]$waterColor, [System.Drawing.Color]$sandColor, [System.Drawing.Color]$leafColor, [System.Drawing.Color]$trunkColor, [bool]$night) {
    $width = 3200
    $height = 2400
    $bitmap = New-Object System.Drawing.Bitmap $width, $height
    $graphics = New-Graphics $bitmap

    $skyBrush = New-Object System.Drawing.Drawing2D.LinearGradientBrush (
        [System.Drawing.Rectangle]::new(0, 0, $width, $height),
        $skyTop,
        $skyBottom,
        90.0
    )
    $graphics.FillRectangle($skyBrush, 0, 0, $width, $height)
    $skyBrush.Dispose()

    $oceanBrush = New-Object System.Drawing.SolidBrush $waterColor
    $graphics.FillRectangle($oceanBrush, 0, [int]($height * 0.28), $width, [int]($height * 0.72))
    $oceanBrush.Dispose()

    for ($i = 0; $i -lt 44; $i++) {
        $alpha = if ($night) { 26 } else { 40 }
        $foamPen = New-Object System.Drawing.Pen (New-Color 255 255 255 $alpha), 2
        $y = 680 + ($i * 22)
        $graphics.DrawArc($foamPen, 160 + (($i % 5) * 430), $y, 520, 52, 0, 180)
        $graphics.DrawArc($foamPen, 260 + (($i % 4) * 600), $y + 8, 380, 38, 0, 180)
        $foamPen.Dispose()
    }

    $sandBrush = New-Object System.Drawing.SolidBrush $sandColor
    foreach ($block in @(
        @{ X = 480; Y = 430; W = 2240; H = 240 },
        @{ X = 320; Y = 670; W = 2580; H = 410 },
        @{ X = 420; Y = 1080; W = 2380; H = 440 },
        @{ X = 640; Y = 1520; W = 1900; H = 360 },
        @{ X = 980; Y = 1880; W = 1180; H = 170 }
    )) {
        $graphics.FillRectangle($sandBrush, $block.X, $block.Y, $block.W, $block.H)
    }
    $sandBrush.Dispose()

    $grassBrush = New-Object System.Drawing.SolidBrush (New-Color 76 152 56 235)
    foreach ($block in @(
        @{ X = 620; Y = 560; W = 1960; H = 260 },
        @{ X = 480; Y = 820; W = 2240; H = 350 },
        @{ X = 620; Y = 1170; W = 1960; H = 360 },
        @{ X = 840; Y = 1530; W = 1540; H = 260 },
        @{ X = 1120; Y = 1790; W = 900; H = 150 }
    )) {
        $graphics.FillRectangle($grassBrush, $block.X, $block.Y, $block.W, $block.H)
    }
    $grassBrush.Dispose()

    $darkGrassBrush = New-Object System.Drawing.SolidBrush (New-Color 53 126 45 180)
    for ($x = 520; $x -lt 2700; $x += 96) {
        for ($y = 610; $y -lt 1900; $y += 80) {
            if ((($x + $y) % 5) -eq 0) {
                $graphics.FillRectangle($darkGrassBrush, $x, $y, 8, 18)
                $graphics.FillRectangle($darkGrassBrush, $x + 10, $y - 10, 8, 28)
                $graphics.FillRectangle($darkGrassBrush, $x + 20, $y + 2, 8, 16)
            }
        }
    }
    $darkGrassBrush.Dispose()

    $cliffTop = New-Object System.Drawing.SolidBrush (New-Color 88 56 38)
    $cliffFace = New-Object System.Drawing.SolidBrush (New-Color 126 76 52)
    $cliffDark = New-Object System.Drawing.SolidBrush (New-Color 62 32 36)
    foreach ($ledge in @(
        @{ X = 480; Y = 805; W = 520; H = 54 },
        @{ X = 1120; Y = 805; W = 640; H = 54 },
        @{ X = 1900; Y = 805; W = 620; H = 54 },
        @{ X = 620; Y = 1150; W = 720; H = 54 },
        @{ X = 1520; Y = 1150; W = 840; H = 54 },
        @{ X = 860; Y = 1510; W = 620; H = 54 },
        @{ X = 1680; Y = 1510; W = 560; H = 54 },
        @{ X = 1100; Y = 1774; W = 820; H = 54 }
    )) {
        $graphics.FillRectangle($cliffTop, $ledge.X, $ledge.Y, $ledge.W, 14)
        $graphics.FillRectangle($cliffFace, $ledge.X, $ledge.Y + 14, $ledge.W, 32)
        $graphics.FillRectangle($cliffDark, $ledge.X, $ledge.Y + 46, $ledge.W, 8)
        for ($sx = $ledge.X; $sx -lt ($ledge.X + $ledge.W); $sx += 32) {
            $graphics.FillRectangle($cliffDark, $sx, $ledge.Y + 6, 12, 8)
        }
    }
    $cliffTop.Dispose()
    $cliffFace.Dispose()
    $cliffDark.Dispose()

    $pathBrush = New-Object System.Drawing.SolidBrush (New-Color 154 102 70 170)
    foreach ($path in @(
        @{ X = 720; Y = 960; W = 320; H = 70 },
        @{ X = 1280; Y = 1380; W = 420; H = 74 },
        @{ X = 1900; Y = 980; W = 330; H = 68 },
        @{ X = 1340; Y = 1690; W = 280; H = 64 }
    )) {
        $graphics.FillRectangle($pathBrush, $path.X, $path.Y, $path.W, $path.H)
    }
    $pathBrush.Dispose()

    if ($night) {
        $moonBrush = New-Object System.Drawing.SolidBrush (New-Color 245 245 220 245)
        $graphics.FillEllipse($moonBrush, 2440, 180, 210, 210)
        $moonBrush.Dispose()

        for ($i = 0; $i -lt 70; $i++) {
            $starBrush = New-Object System.Drawing.SolidBrush (New-Color 255 255 235 (120 + ($i % 120)))
            $x = (Get-Random -Minimum 0 -Maximum $width)
            $y = (Get-Random -Minimum 0 -Maximum 620)
            $size = Get-Random -Minimum 2 -Maximum 5
            $graphics.FillEllipse($starBrush, $x, $y, $size, $size)
            $starBrush.Dispose()
        }
    }
    else {
        $sunBrush = New-Object System.Drawing.SolidBrush (New-Color 255 241 148 220)
        $graphics.FillEllipse($sunBrush, 2460, 170, 230, 230)
        $sunBrush.Dispose()
    }

    $overlayColor = if ($night) { New-Color 12 24 60 64 } else { New-Color 255 200 120 18 }
    $overlayBrush = New-Object System.Drawing.SolidBrush $overlayColor
    $graphics.FillRectangle($overlayBrush, 0, 0, $width, $height)
    $overlayBrush.Dispose()
    $graphics.Dispose()

    Save-Bitmap $bitmap (Join-Path $textureDir $name)
}

function Create-UnitSprite([string]$name, [System.Drawing.Color]$bodyColor, [System.Drawing.Color]$accentColor, [bool]$zombie) {
    $bitmap = New-Object System.Drawing.Bitmap 96, 96
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)

    $shadow = New-Object System.Drawing.SolidBrush (New-Color 0 0 0 50)
    $graphics.FillRectangle($shadow, 18, 72, 60, 10)
    $shadow.Dispose()

    $bodyBrush = New-Object System.Drawing.SolidBrush $bodyColor
    $accentBrush = New-Object System.Drawing.SolidBrush $accentColor
    $outlinePen = New-Object System.Drawing.Pen (New-Color 30 20 15), 4

    $graphics.FillRectangle($bodyBrush, 28, 16, 40, 10)
    $graphics.FillRectangle($bodyBrush, 24, 26, 48, 20)
    $graphics.DrawRectangle($outlinePen, 24, 16, 48, 30)
    $graphics.FillPolygon($bodyBrush, @(
        [System.Drawing.Point]::new(22, 46),
        [System.Drawing.Point]::new(74, 46),
        [System.Drawing.Point]::new(68, 70),
        [System.Drawing.Point]::new(30, 70)
    ))
    $graphics.DrawPolygon($outlinePen, @(
        [System.Drawing.Point]::new(22, 46),
        [System.Drawing.Point]::new(74, 46),
        [System.Drawing.Point]::new(68, 70),
        [System.Drawing.Point]::new(30, 70)
    ))
    $graphics.FillRectangle($accentBrush, 34, 26, 8, 8)
    $graphics.FillRectangle($accentBrush, 54, 26, 8, 8)

    if ($zombie) {
        $mouthPen = New-Object System.Drawing.Pen (New-Color 160 30 30), 3
        $graphics.DrawLine($mouthPen, 36, 40, 60, 44)
        $graphics.DrawLine($mouthPen, 40, 48, 54, 40)
        $mouthPen.Dispose()
        $graphics.DrawLine($outlinePen, 22, 52, 8, 62)
        $graphics.DrawLine($outlinePen, 74, 54, 86, 64)
    }
    else {
        $graphics.FillPolygon($accentBrush, @(
            [System.Drawing.Point]::new(38, 42),
            [System.Drawing.Point]::new(50, 36),
            [System.Drawing.Point]::new(58, 43),
            [System.Drawing.Point]::new(50, 56)
        ))
        $graphics.DrawLine($outlinePen, 20, 40, 10, 32)
        $graphics.DrawLine($outlinePen, 76, 42, 86, 34)
    }

    $graphics.DrawLine($outlinePen, 34, 68, 26, 90)
    $graphics.DrawLine($outlinePen, 60, 68, 70, 90)

    if ($zombie) {
        $tearBrush = New-Object System.Drawing.SolidBrush (New-Color 58 88 62)
        $graphics.FillRectangle($tearBrush, 24, 58, 14, 8)
        $graphics.FillRectangle($tearBrush, 58, 50, 14, 10)
        $tearBrush.Dispose()
    }
    else {
        $bandBrush = New-Object System.Drawing.SolidBrush (New-Color 230 206 112)
        $graphics.FillRectangle($bandBrush, 26, 18, 44, 6)
        $graphics.FillRectangle($bandBrush, 18, 52, 10, 8)
        $graphics.FillRectangle($bandBrush, 68, 52, 10, 8)
        $bandBrush.Dispose()
    }

    $bodyBrush.Dispose()
    $accentBrush.Dispose()
    $outlinePen.Dispose()
    $graphics.Dispose()

    Save-Bitmap $bitmap (Join-Path $textureDir $name)
}

function Create-PlayerSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 96, 96
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)

    $shadow = New-Object System.Drawing.SolidBrush (New-Color 0 0 0 50)
    $graphics.FillRectangle($shadow, 18, 72, 60, 10)
    $shadow.Dispose()

    $shirt = New-Object System.Drawing.SolidBrush (New-Color 58 128 86)
    $skin = New-Object System.Drawing.SolidBrush (New-Color 226 188 150)
    $pants = New-Object System.Drawing.SolidBrush (New-Color 72 62 108)
    $hair = New-Object System.Drawing.SolidBrush (New-Color 72 42 24)
    $outline = New-Object System.Drawing.Pen (New-Color 24 24 24), 4

    $graphics.FillRectangle($skin, 28, 18, 40, 30)
    $graphics.FillRectangle($hair, 30, 14, 36, 12)
    $graphics.FillRectangle($shirt, 22, 42, 52, 22)
    $graphics.FillRectangle($pants, 28, 62, 38, 16)
    $graphics.DrawRectangle($outline, 28, 18, 40, 30)
    $graphics.DrawRectangle($outline, 22, 42, 52, 22)
    $graphics.DrawRectangle($outline, 28, 62, 38, 16)
    $graphics.DrawLine($outline, 22, 48, 10, 56)
    $graphics.DrawLine($outline, 74, 48, 86, 56)
    $graphics.DrawLine($outline, 38, 78, 30, 92)
    $graphics.DrawLine($outline, 58, 78, 66, 92)

    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 30 30 30)), 38, 30, 6, 6)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 30 30 30)), 54, 30, 6, 6)

    $shirt.Dispose()
    $skin.Dispose()
    $pants.Dispose()
    $hair.Dispose()
    $outline.Dispose()
    $graphics.Dispose()

    Save-Bitmap $bitmap (Join-Path $textureDir "player_body.png")
}

function Create-PistolSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 96, 32
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)

    $metal = New-Object System.Drawing.SolidBrush (New-Color 70 78 92)
    $highlight = New-Object System.Drawing.SolidBrush (New-Color 144 154 172)
    $grip = New-Object System.Drawing.SolidBrush (New-Color 96 64 42)
    $outline = New-Object System.Drawing.Pen (New-Color 22 22 22), 3

    $graphics.FillRectangle($metal, 18, 10, 48, 12)
    $graphics.FillRectangle($highlight, 22, 8, 26, 4)
    $graphics.FillRectangle($metal, 62, 12, 18, 7)
    $graphics.FillPolygon($grip, @(
        [System.Drawing.Point]::new(34, 18),
        [System.Drawing.Point]::new(50, 18),
        [System.Drawing.Point]::new(45, 30),
        [System.Drawing.Point]::new(33, 28)
    ))
    $graphics.DrawRectangle($outline, 18, 10, 48, 12)
    $graphics.DrawLine($outline, 66, 12, 80, 12)
    $graphics.DrawLine($outline, 66, 19, 80, 19)
    $graphics.DrawPolygon($outline, @(
        [System.Drawing.Point]::new(34, 18),
        [System.Drawing.Point]::new(50, 18),
        [System.Drawing.Point]::new(45, 30),
        [System.Drawing.Point]::new(33, 28)
    ))

    $metal.Dispose()
    $highlight.Dispose()
    $grip.Dispose()
    $outline.Dispose()
    $graphics.Dispose()

    Save-Bitmap $bitmap (Join-Path $textureDir "pistol.png")
}

function Create-AxeSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 64, 96
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)

    $handle = New-Object System.Drawing.SolidBrush (New-Color 108 70 42)
    $handleLight = New-Object System.Drawing.SolidBrush (New-Color 166 104 58)
    $metal = New-Object System.Drawing.SolidBrush (New-Color 156 168 178)
    $metalDark = New-Object System.Drawing.SolidBrush (New-Color 76 88 102)
    $outline = New-Object System.Drawing.Pen (New-Color 18 18 22), 3

    $graphics.FillRectangle($handle, 28, 18, 10, 70)
    $graphics.FillRectangle($handleLight, 38, 22, 4, 58)
    $graphics.DrawRectangle($outline, 28, 18, 14, 70)
    $graphics.FillPolygon($metal, @(
        [System.Drawing.Point]::new(8, 14),
        [System.Drawing.Point]::new(32, 4),
        [System.Drawing.Point]::new(54, 14),
        [System.Drawing.Point]::new(48, 36),
        [System.Drawing.Point]::new(32, 28),
        [System.Drawing.Point]::new(16, 36)
    ))
    $graphics.FillRectangle($metalDark, 28, 18, 10, 14)
    $graphics.DrawPolygon($outline, @(
        [System.Drawing.Point]::new(8, 14),
        [System.Drawing.Point]::new(32, 4),
        [System.Drawing.Point]::new(54, 14),
        [System.Drawing.Point]::new(48, 36),
        [System.Drawing.Point]::new(32, 28),
        [System.Drawing.Point]::new(16, 36)
    ))

    $handle.Dispose()
    $handleLight.Dispose()
    $metal.Dispose()
    $metalDark.Dispose()
    $outline.Dispose()
    $graphics.Dispose()
    Save-Bitmap $bitmap (Join-Path $textureDir "axe.png")
}

function Create-BulletSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 32, 12
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 255 241 170)), 0, 2, 26, 8)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 210 160 60)), 18, 2, 12, 8)
    $graphics.Dispose()
    Save-Bitmap $bitmap (Join-Path $textureDir "bullet.png")
}

function Create-TreeSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 128, 160
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 0 0 0 55)), 28, 128, 72, 16)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 104 70 40)), 54, 80, 20, 54)
    $leafBrush = New-Object System.Drawing.SolidBrush (New-Color 40 128 64)
    foreach ($leaf in @(
        @{X=30;Y=42;W=42;H=36}, @{X=54;Y=24;W=44;H=42}, @{X=70;Y=52;W=38;H=36},
        @{X=20;Y=64;W=46;H=34}, @{X=48;Y=60;W=54;H=42}
    )) { $graphics.FillRectangle($leafBrush, $leaf.X, $leaf.Y, $leaf.W, $leaf.H) }
    $leafBrush.Dispose()
    $graphics.Dispose()
    Save-Bitmap $bitmap (Join-Path $textureDir "tree.png")
}

function Create-RockSprite() {
    $bitmap = New-Object System.Drawing.Bitmap 160, 110
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $graphics.FillRectangle((New-Object System.Drawing.SolidBrush (New-Color 0 0 0 45)), 24, 84, 102, 14)
    $rockBrush = New-Object System.Drawing.SolidBrush (New-Color 106 110 118)
    $graphics.FillPolygon($rockBrush, @(
        [System.Drawing.Point]::new(18, 78),
        [System.Drawing.Point]::new(34, 40),
        [System.Drawing.Point]::new(64, 20),
        [System.Drawing.Point]::new(112, 28),
        [System.Drawing.Point]::new(138, 54),
        [System.Drawing.Point]::new(122, 84),
        [System.Drawing.Point]::new(66, 90)
    ))
    $rockBrush.Dispose()
    $graphics.Dispose()
    Save-Bitmap $bitmap (Join-Path $textureDir "rock.png")
}

function Create-Panel() {
    $bitmap = New-Object System.Drawing.Bitmap 320, 120
    $graphics = New-Graphics $bitmap
    $graphics.Clear([System.Drawing.Color]::Transparent)
    $panelBrush = New-Object System.Drawing.SolidBrush (New-Color 10 28 30 185)
    $panelBorder = New-Object System.Drawing.Pen (New-Color 240 220 170 210), 3
    $graphics.FillRectangle($panelBrush, 8, 8, 304, 104)
    $graphics.DrawRectangle($panelBorder, 8, 8, 304, 104)
    $panelBrush.Dispose()
    $panelBorder.Dispose()
    $graphics.Dispose()
    Save-Bitmap $bitmap (Join-Path $textureDir "hud_panel.png")
}

function Write-Wav([string]$path, [double[]]$samples, [int]$sampleRate) {
    $stream = [System.IO.File]::Create($path)
    $writer = New-Object System.IO.BinaryWriter($stream)
    $subChunk2Size = $samples.Length * 2
    $chunkSize = 36 + $subChunk2Size

    $writer.Write([System.Text.Encoding]::ASCII.GetBytes("RIFF"))
    $writer.Write([int]$chunkSize)
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes("WAVE"))
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes("fmt "))
    $writer.Write([int]16)
    $writer.Write([int16]1)
    $writer.Write([int16]1)
    $writer.Write([int]$sampleRate)
    $writer.Write([int]($sampleRate * 2))
    $writer.Write([int16]2)
    $writer.Write([int16]16)
    $writer.Write([System.Text.Encoding]::ASCII.GetBytes("data"))
    $writer.Write([int]$subChunk2Size)

    foreach ($sample in $samples) {
        $clamped = [Math]::Max(-1.0, [Math]::Min(1.0, $sample))
        $writer.Write([int16]([Math]::Round($clamped * 32767)))
    }

    $writer.Dispose()
    $stream.Dispose()
}

function Generate-ToneSamples([double]$durationSeconds, [int]$sampleRate, [scriptblock]$formula) {
    $count = [int]($durationSeconds * $sampleRate)
    $samples = New-Object double[] $count
    for ($i = 0; $i -lt $count; $i++) {
        $t = $i / $sampleRate
        $samples[$i] = & $formula $t
    }
    return $samples
}

function New-Noise([double]$amount) {
    return ((Get-Random -Minimum -1000 -Maximum 1000) / 1000.0) * $amount
}

$sampleRate = 44100

$shootSamples = Generate-ToneSamples 0.14 $sampleRate {
    param($t)
    $envelope = [Math]::Exp(-24 * $t)
    $tone = [Math]::Sin(2 * [Math]::PI * 780 * $t) * 0.45
    $noise = New-Noise 0.35
    return ($tone + $noise) * $envelope
}
Write-Wav (Join-Path $soundDir "shoot.wav") $shootSamples $sampleRate

$hitSamples = Generate-ToneSamples 0.18 $sampleRate {
    param($t)
    $envelope = [Math]::Exp(-18 * $t)
    $tone = [Math]::Sin(2 * [Math]::PI * 110 * $t) * 0.55
    $click = [Math]::Sin(2 * [Math]::PI * 220 * $t) * 0.22
    return ($tone + $click + (New-Noise 0.15)) * $envelope
}
Write-Wav (Join-Path $soundDir "hit.wav") $hitSamples $sampleRate

$daySamples = Generate-ToneSamples 12.0 $sampleRate {
    param($t)
    $wave = (
        [Math]::Sin(2 * [Math]::PI * 220 * $t) * 0.12 +
        [Math]::Sin(2 * [Math]::PI * 277 * $t) * 0.08 +
        [Math]::Sin(2 * [Math]::PI * 330 * $t) * 0.07 +
        [Math]::Sin(2 * [Math]::PI * 0.25 * $t) * 0.03
    )
    $sea = [Math]::Sin(2 * [Math]::PI * 55 * $t) * 0.03 + (New-Noise 0.01)
    return $wave + $sea
}
Write-Wav (Join-Path $soundDir "day_theme.wav") $daySamples $sampleRate

$nightSamples = Generate-ToneSamples 12.0 $sampleRate {
    param($t)
    $wave = (
        [Math]::Sin(2 * [Math]::PI * 110 * $t) * 0.15 +
        [Math]::Sin(2 * [Math]::PI * 165 * $t) * 0.07 +
        [Math]::Sin(2 * [Math]::PI * 0.18 * $t) * 0.04
    )
    $air = [Math]::Sin(2 * [Math]::PI * 36 * $t) * 0.025 + (New-Noise 0.012)
    return $wave + $air
}
Write-Wav (Join-Path $soundDir "night_theme.wav") $nightSamples $sampleRate

Create-Background "island_day.png" (New-Color 127 212 255) (New-Color 205 244 255) (New-Color 36 134 176) (New-Color 226 205 128) (New-Color 44 140 76) (New-Color 96 68 44) $false
Create-Background "island_sunset.png" (New-Color 252 144 82) (New-Color 255 213 150) (New-Color 44 102 150) (New-Color 222 182 114) (New-Color 58 118 62) (New-Color 90 60 38) $false
Create-Background "island_night.png" (New-Color 14 28 68) (New-Color 44 70 118) (New-Color 14 72 118) (New-Color 126 114 92) (New-Color 42 90 58) (New-Color 74 54 42) $true
Create-PlayerSprite
Create-PistolSprite
Create-AxeSprite
Create-TreeSprite
Create-RockSprite
Create-UnitSprite "cannibal.png" (New-Color 196 122 64) (New-Color 120 18 18) $false
Create-UnitSprite "zombie.png" (New-Color 112 146 106) (New-Color 214 40 40) $true
Create-BulletSprite
Create-Panel
