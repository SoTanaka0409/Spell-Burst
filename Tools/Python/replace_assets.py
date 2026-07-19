import os
import glob

replacements = {
    '"Resource/background.png"': '"IMG_BG_TITLE"',
    '"Resource/bg_phase1.png"': '"IMG_BG_PHASE1"',
    '"Resource/bg_phase2.png"': '"IMG_BG_PHASE2"',
    '"Resource/bg_phase3.png"': '"IMG_BG_PHASE3"',
    '"Resource/bg_boss.png"': '"IMG_BG_BOSS"',
    '"Resource/モ～たまらん爽快な牧場の風景 - コピー.png"': '"IMG_BG_PASTURE"',
    '"Resource/player.png"': '"IMG_CHARA_PLAYER1"',
    '"Resource/player2.png"': '"IMG_CHARA_PLAYER2"',
    '"Resource/player3.png"': '"IMG_CHARA_PLAYER3"',
    '"Resource/enemy.png"': '"IMG_CHARA_ENEMY"',
    '"Resource/boss.png"': '"IMG_CHARA_BOSS"',
    '"Resource/cutin_girl.png"': '"IMG_CUTIN_GIRL"',
    '"Resource/cutin_mackerel.png"': '"IMG_CUTIN_MACKEREL"',
    '"Resource/cutin_normal.png"': '"IMG_CUTIN_NORMAL"',
    '"Resource/cutin_old.png"': '"IMG_CUTIN_OLD"',
    '"Resource/ui_button.png"': '"IMG_UI_BTN_BASE"',
    '"Resource/スタートボタン1.png"': '"IMG_UI_BTN_START"',
    '"Resource/名称未設定 1.png"': '"IMG_UI_MISC1"',
    '"Resource/rule1.png"': '"IMG_RULE_01"',
    '"Resource/rule2.png"': '"IMG_RULE_02"',
    '"Resource/rule3.png"': '"IMG_RULE_03"',
    '"Resource/rule4.png"': '"IMG_RULE_04"',
    '"Resource/rule5.png"': '"IMG_RULE_05"',
    '"Resource/rule6.png"': '"IMG_RULE_06"',
    '"Resource/rock.png"': '"IMG_OBJ_ROCK"',
    '"Resource/3d_enemy_fish.png"': '"TEX_ENEMY_FISH"',
    '"Resource/3d_merman.png"': '"TEX_ENEMY_MERMAN"',
    '"Resource/title_bg.mp4"': '"MOV_TITLE_BG"',
    '"Resource/se_click.wav"': '"SE_UI_CLICK"',
    '"Resource/BGM/MusMus-BGM-096.mp3"': '"BGM_096"',
    '"Resource/BGM/MusMus-BGM-112.mp3"': '"BGM_112"',
    '"Resource/BGM/MusMus-BGM-115.mp3"': '"BGM_115"',
    '"Resource/BGM/MusMus-BGM-146.mp3"': '"BGM_146"',
    '"Resource/BGM/MusMus-BGM-169.mp3"': '"BGM_169"',
    '"Resource/BGM/MusMus-BGM-170.mp3"': '"BGM_170"',
    '"Resource/SE/se_barrier_hit.mp3"': '"SE_BARRIER_HIT"',
    '"Resource/SE/se_button1.mp3"': '"SE_BTN1"',
    '"Resource/SE/se_destroy_glass01.mp3"': '"SE_GLASS_DESTROY"',
    '"Resource/SE/se_glass1.mp3"': '"SE_GLASS1"',
    '"Resource/SE/se_hit1.mp3"': '"SE_HIT1"',
    '"Resource/SE/se_shoot1.mp3"': '"SE_SHOOT1"',
    '"Resource/SE/se_sound1.mp3"': '"SE_SOUND1"',
    '"Resource/SE/se_sound2.mp3"': '"SE_SOUND2"',
    '"Resource/SE/se_sound3.mp3"': '"SE_SOUND3"',
    '"Resource/SE/se_sound4.mp3"': '"SE_SOUND4"',
    '"Resource/SE/se_sound5.mp3"': '"SE_SOUND5"',
    '"Resource/SE/se_sound6.mp3"': '"SE_SOUND6"',
    '"Resource/SE/se_sound7.mp3"': '"SE_SOUND7"',
    '"Resource/SE/se_sound8.mp3"': '"SE_SOUND8"',
    '"Resource/SE/se_sound9.mp3"': '"SE_SOUND9"',
    '"Resource/SE/se_sound10.mp3"': '"SE_SOUND10"',
    '"Resource/SE/se_sound11.mp3"': '"SE_SOUND11"',
    '"Resource/SE/se_sound12.mp3"': '"SE_SOUND12"',
    '"Resource/SE/se_sound13.mp3"': '"SE_SOUND13"',
    '"Resource/SE/se_status_up.mp3"': '"SE_STATUS_UP"',
    '"Resource/SE/se_unknown1.mp3"': '"SE_UNKNOWN1"',
    
    # Check for paths without leading "Resource/" just in case, though they usually have it.
}

files = glob.glob('Source/**/*.cpp', recursive=True) + glob.glob('Source/**/*.h', recursive=True)

for file_path in files:
    with open(file_path, 'r', encoding='utf-8-sig', errors='ignore') as f:
        content = f.read()
    
    original_content = content
    for old, new in replacements.items():
        content = content.replace(old, new)
        
    if content != original_content:
        print(f"Updated {file_path}")
        with open(file_path, 'w', encoding='utf-8-sig') as f:
            f.write(content)
