#ifndef AUTH_H
#define false 1
#define true 0

#define BOT_TOKEN "Mzc3NjEyMzAyNTIzODI2MTc3.YHDcbA.3qnUrD2FWTuHAsBlC0lLO828iHo"
#define IS_BOT false

#ifdef BOT_TOKEN
#if (IS_BOT == false)
#define BOT_HEADERS "{ \"Content-Type\": \"application/json\", \"Authorization\": \"Mzc3NjEyMzAyNTIzODI2MTc3.YHDcbA.3qnUrD2FWTuHAsBlC0lLO828iHo\" }"
#endif

#if (IS_BOT == true)
#define BOT_HEADERS "{ \"Content-Type\": \"application/json\", \"Authorization\": \"Bot Mzc3NjEyMzAyNTIzODI2MTc3.YHDcbA.3qnUrD2FWTuHAsBlC0lLO828iHo\" }"
#endif

#endif
#endif
