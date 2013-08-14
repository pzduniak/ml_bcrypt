/*********************************************************
*
*  Multi Theft Auto: San Andreas - Deathmatch
*
*  ml_base, External lua add-on module
*
*  Copyright � 2003-2008 MTA.  All Rights Reserved.
*
*  Grand Theft Auto is � 2002-2003 Rockstar North
*
*  THE FOLLOWING SOURCES ARE PART OF THE MULTI THEFT
*  AUTO SOFTWARE DEVELOPMENT KIT AND ARE RELEASED AS
*  OPEN SOURCE FILES. THESE FILES MAY BE USED AS LONG
*  AS THE DEVELOPER AGREES TO THE LICENSE THAT IS
*  PROVIDED WITH THIS PACKAGE.
*
*********************************************************/

#include "CFunctions.h"
#include "extra/CLuaArguments.h"

extern "C"
{
	#include "ow-crypt.h"
}

#ifndef WIN32
	#include <fcntl.h>
#endif

#define HASH_SIZE 184
#define SALT_SIZE 128
#define ENTROPY_SIZE 32

static int urandom;

#ifdef WIN32
	#include <windows.h>
	#include <wincrypt.h>

	static unsigned long rng_win32(unsigned char *buf, unsigned long len)
	{
	   HCRYPTPROV hProv = 0;
	   if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL,
								(CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET)) &&
		   !CryptAcquireContext (&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL,
								CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET | CRYPT_NEWKEYSET))
		  return 0;
 
	   if (CryptGenRandom(hProv, len, buf) == TRUE) {
		  CryptReleaseContext(hProv, 0);
		  return len;
	   } else {
		  CryptReleaseContext(hProv, 0);
		  return 0;
	   }
	}
#else
	void randomBytes( char* output, size_t bytes ) {
		urandom = open( "/dev/urandom", O_RDONLY );
		read( urandom, output, bytes );
	}
#endif


int CFunctions::BcryptDigest ( lua_State* L )
{
    if ( L )
    {
		const char* key = luaL_checkstring( L, 1 );
		const char* salt = luaL_checkstring( L, 2 );

		char hash[ HASH_SIZE ];
        crypt_rn( key, salt, hash, HASH_SIZE );

		lua_pushlstring( L, hash, HASH_SIZE );

		return 1;
    }

	lua_pushboolean( L, false );
    return 1;
}

int CFunctions::BcryptSalt( lua_State* L ) {
    if ( L )
    {
		unsigned long logRounds = luaL_checkinteger( L, 1 );

		char salt[ SALT_SIZE ];
		char entropy[ENTROPY_SIZE];

		#ifdef WIN32
			rng_win32((unsigned char*)entropy, sizeof(entropy));
		#else
			randomBytes( entropy, sizeof( entropy ) );
		#endif
		
		crypt_gensalt_rn( "$2y$", logRounds, entropy, sizeof( entropy ), salt, sizeof( salt ) );

		lua_pushlstring( L, salt, sizeof( salt ) );

		return 1;
	}

	lua_pushboolean( L, false );
	return 1;
}

int CFunctions::BcryptVerify( lua_State* L ) {
    if ( L )
    {
		const char* key = luaL_checkstring( L, 1 );
		const char* digest = luaL_checkstring( L, 2 );

		char hash[ HASH_SIZE ];
		memset( hash, 0, sizeof( hash ) );

		crypt_rn( key, digest, hash, sizeof( hash ) );

		int verified = strncmp( hash, digest, sizeof( hash ) ) == 0;

		lua_pushboolean( L, verified );

		return 1;
	}

	lua_pushboolean( L, false );
	return 1;
}