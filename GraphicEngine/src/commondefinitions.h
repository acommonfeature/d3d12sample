#ifdef _MSC_VER
#define GRAPHIC_CALL_TYPE __cdecl
#else
#define GRAPHIC_CALL_TYPE
#endif

#ifdef __cplusplus
#define GRAPHIC_BEGIN_NAMESPACE(Name)\
	namespace Name					 \
	{
#define GRAPHIC_END_NAMESPACE }
#endif