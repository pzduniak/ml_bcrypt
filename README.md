ml_bcrypt - MTA bcrypt module
=========

Bcrypt module for MTA:SA, for your passwords. Just three handy functions: `bcrypt_digest`, `bcrypt_salt`, and `bcrypt_verify`.

bcrypt_digest
-------------
    string bcrypt_digest(string key, string salt)
Returns the hash.

bcrypt_salt
-----------
    string bcrypt_salt(int logRounds)
Please visit [this link](http://security.stackexchange.com/questions/17207/recommended-of-rounds-for-bcrypt) to determine the number of rounds appropriate for your server.
Returns the salt.

bcrypt_verify
-------------
    bool bcrypt_verify(string key, string digest)
Returns whether it is verified.
