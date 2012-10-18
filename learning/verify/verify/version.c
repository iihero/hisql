#define __STRINGIFY(x) #x
#define __STRINGIFY2(z) __STRINGIFY(z)
#define PG_VERSION_STR "PostgreSQL 9.2.1, compiled by Visual C++ build " __STRINGIFY2(_MSC_VER) ", 32-bit"

#include <stdio.h>

struct varlena
{
	char		vl_len_[4];		/* Do not touch this field directly! */
	char		vl_dat[1];
};

#define VARHDRSZ		((int) sizeof(int))


typedef struct varlena text;


#ifndef HAVE_INT8
typedef signed char int8;		/* == 8 bits */
typedef signed short int16;		/* == 16 bits */
typedef signed int int32;		/* == 32 bits */
#endif   /* not HAVE_INT8 */

/*
 * uintN
 *		Unsigned integer, EXACTLY N BITS IN SIZE,
 *		used for numerical computations and the
 *		frontend/backend protocol.
 */
#ifndef HAVE_UINT8
typedef unsigned char uint8;	/* == 8 bits */
typedef unsigned short uint16;	/* == 16 bits */
typedef unsigned int uint32;	/* == 32 bits */
#endif   /* not HAVE_UINT8 */

/*
 * These structs describe the header of a varlena object that may have been
 * TOASTed.  Generally, don't reference these structs directly, but use the
 * macros below.
 *
 * We use separate structs for the aligned and unaligned cases because the
 * compiler might otherwise think it could generate code that assumes
 * alignment while touching fields of a 1-byte-header varlena.
 */
typedef union
{
	struct						/* Normal varlena (4-byte length) */
	{
		uint32		va_header;
		char		va_data[1];
	}			va_4byte;
	struct						/* Compressed-in-line format */
	{
		uint32		va_header;
		uint32		va_rawsize; /* Original data size (excludes header) */
		char		va_data[1]; /* Compressed data */
	}			va_compressed;
} varattrib_4b;

#define SET_VARSIZE(PTR, len)				SET_VARSIZE_4B(PTR, len)
#define SET_VARSIZE_4B(PTR,len) \
	(((varattrib_4b *) (PTR))->va_4byte.va_header = (((uint32) (len)) << 2))


#define VARDATA_4B(PTR)		(((varattrib_4b *) (PTR))->va_4byte.va_data)
#define VARDATA(PTR)						VARDATA_4B(PTR)

#define VARSIZE_4B(PTR) \
	((((varattrib_4b *) (PTR))->va_4byte.va_header >> 2) & 0x3FFFFFFF)
#define VARSIZE(PTR)						VARSIZE_4B(PTR)

typedef _W64 unsigned int   uintptr_t;
typedef uintptr_t Datum;
#define PointerGetDatum(X) ((Datum) (X))
#define PG_RETURN_POINTER(x) return PointerGetDatum(x)
#define PG_RETURN_TEXT_P(x)    PG_RETURN_POINTER(x)

typedef char *Pointer;
#define DatumGetPointer(X) ((Pointer) (X))
/*
 * DatumGetCString
 *		Returns C string (null-terminated string) value of a datum.
 *
 * Note: C string is not a full-fledged Postgres type at present,
 * but type input functions use this conversion for their inputs.
 */

#define DatumGetCString(X) ((char *) DatumGetPointer(X))



text* cstring_to_text(const char* version)
{
    int len = strlen(version);

	text	   *result = (text *) malloc(len + VARHDRSZ);

	SET_VARSIZE(result, len + VARHDRSZ);
	memcpy(VARDATA(result), version, len);

	return result;    
}

Datum pgsql_version()
{
    PG_RETURN_TEXT_P(cstring_to_text(PG_VERSION_STR));
}




int main()
{
    text* abc = NULL;
    Datum v;
    char* version0;
    char* version;
    int vsize;
    printf("%s\n", PG_VERSION_STR);
    abc = cstring_to_text(PG_VERSION_STR);
    free(abc);

    v = pgsql_version();
    /*
    version0 = DatumGetCString(v);
    */
    version = VARDATA(v);
    vsize = VARSIZE(v) - VARHDRSZ;
    *(version + vsize) = '\0';

    printf("new version result = %s\n", version);

    return 0;
}
