# Build firmware
`docker compose run --rm qmk`

**.build** ディレクトリに左右それぞれに対応したHexファイルが生成される
- 左手：keyball_rev1_ball_via_acc_left.hex
- 右手：keyball_rev1_noball_via_acc_left.hex

# Write firmware
1. qmktoolboxでHexファイルをセットして **Auto-Flash** にチェックを入れる(書き込むHexファイルが右手用か左手用かを確認)
1. キーボードのリセットボタンをおす

# Custom
1. **qmk_firmware/keyboards/keyball/keymaps/via_acc_left** を複製して名前を変える
1. **docker-compose.yml** のenvironmentのKEYMAPを変更した名前に書き換える

## Remap
Remapに対応させるときは，**qmk_firmware/keyboards/keyball/keymaps/via_acc_left/rules.mk** の `VIA_ENABLE = no`を`VIA_ENABLE = yes` にする