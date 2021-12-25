#ifndef DISPAUTH_H_
#define DISPAUTH_H_

#define AUTH_NG 1 // îFèÿNG main.cppÇ≈égóp

class DispAuth{
    char password[4];
    public:
    DispAuth();
    DispAuth(char *password);
    void DispLock();
    void DispPassword(char *passcode);
    void DispUnlock();
    char passCheck(char *pass);
};

#endif /* DISPAUTH_H_ */