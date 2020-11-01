#pragma once

#if NDEBUG
#define DO_TEST(expresion) void (0);
#else
#define DO_TEST(expresion) Log_Of_MyTests(expresion, __LINE__, __FILE__, __FUNCTION__, #expresion);
#endif

void NewTests();
void Log_Of_MyTests( bool valid, int line, const char* file, const char* fuNname, const char* expresion);
void EndTests(  );
