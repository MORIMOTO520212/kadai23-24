/*
 * DispAuth.cpp
 * 説明：パスワードの照合＆ロック画面の表示
 *
 * Created: 2021/12/22 11:44:24
 * Author : YUMA.morimoto
 */

#include "common.h"
#include "DispAuth.h"
#include "lcd.h"

LCD lcd;

DispAuth::DispAuth(void){
    // 初期化　＊パスワードがセットされなかった場合に仮で
    //　　　　　 1234をセットする
    for(int i=0; i<4; i++){
        this->password[i] = i+1;
    }
}
DispAuth::DispAuth(char *password){
    // 初期化
    for(int i=0; i<4; i++){ // パスワードセット
        this->password[i] = password[i];
    }
}

/* ロック画面の表示 */
void DispAuth::DispLock(){
    lcd.lcdClr(); // 画面初期化
    char lockedText[] = "Locked!";
    char pushText[] = "Push Button!";
    // 1行目  ＊一文字ずつlcdPrint関数でセットする
    for(int i=0; i<15; i++) lcd.lcdPrint(i, 0, "*");
    // 2行目
    for(int i=0; i<4;  i++) lcd.lcdPrint(i, 1, "*");
    for(int i=0; i<7;  i++) lcd.lcdPrint(i, 1, &lockedText[i]);
    for(int i=0; i<5;  i++) lcd.lcdPrint(i, 1, "*");
    // 3行目
    for(int i=0; i<2;  i++)  lcd.lcdPrint(i, 2, "*");
    for(int i=0; i<12;  i++) lcd.lcdPrint(i, 2, &pushText[i]);
    for(int i=0; i<2;  i++)  lcd.lcdPrint(i, 2, "*");
    // 4行目
    for(int i=0; i<15; i++) lcd.lcdPrint(i, 0, "*");
    lcd.lcdFlip(); // 画面表示
}

/* アンロック画面の表示 */
void DispAuth::DispUnlock(void){
    // DispLock関数と同じように記述
}

/* パスワード入力画面 */
void DispAuth::DispPassword(char *passcode){
    // DispLock関数と同じように記述
    // passcodeは入力されたパスワードの変数
}

char DispAuth::passCheck(char *pass){
    // 引数から入力されたパスワードを受け取って照合
    // パスワードはバイナリで受け取る 0xFF以降は無効とする
    // 【戻り値】
    // 0 - 認証OK
    // 1 - 認証NG
    char authResult = 0;
    char *password;
    password = this->password;
    for(int i=0; i<4; i++){
        if(!(password[i] == pass[i])) authResult = 1;
    }
    return authResult;
}