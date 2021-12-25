/*
 * main.cpp
 * Created: 2021/12/22 11:44:24
 * Author : YUMA.morimoto
 */ 

#include "common.h"
#include "DispAuth.h"
#include "Number.h"
#include "Button.h"

int main(){
    char pass[4]={1,2,3,4};
    char passcode[4];          // ���̓p�X���[�h��ۑ����郁����
    int lock = AUTH_NG;
    Button   b1;               // button�C���X�^���X����
    DispAuth d1(pass);         // l1�C���X�^���X����
    Number   n1;               // n1�C���X�^���X����
    UCHR     digit[2];         // �����͒l[0]:
    digit[0] = n1.getNumber(); // digit�����l
    
    while(1){                  // �������[�v
        if(lock == AUTH_NG){   // �p�X���[�h���s��v�̎�
            d1.DispLock();     // Lock��ʕ\��
        }else{                 // �p�X���[�h����v�̎�
            d1.DispUnlock();   // UnLock��ʕ\��
        }
        while(b1.buttonCheck() != SW_ON);  //button�����������܂ő҂�
        while(b1.buttonCheck() != SW_OFF); //button�����������܂ő҂�
        for(int i=0; i<4; i++){           //4�����̃p�X���[�h��������
            passcode[i] = 0xFF;
        }
        for(int i=0; i<4; i++){                 // 4�����J��Ԃ��ē����
            digit[1] = -1;                      // digit �O��̒l�ɍ���̒l�ƈقȂ�悤�ɐݒ�
            while(b1.buttonCheck() == SW_OFF){  // �X�C�b�`��OFF��Ԃ̎��ɐ��l��荞�݂�����
                digit[0] = n1.getNumber();      // ���l��荞�ݒl
                if(digit[0] != digit[1]){       // ���l���ω������Ƃ�
                    digit[1]    = digit[0];     // �O�񐔒l�X�V
                    passcode[1] = digit[0];     // ���͂����p�X�R�[�h�̒l���X�V
                    d1.DispPassword(passcode);  // ���͂����p�X���[�h��\��
                }
            }
            while(b1.buttonCheck() != SW_OFF);  // �X�C�b�`��OFF��Ԃ��Ȃ�܂ő҂���������
        }
        lock = d1.passCheck(passcode);          // �p�X���[�h��v�`�F�b�N
    }
    return 0;
}