add_library(ex_account)

target_sources(ex_account
    PRIVATE
        Account.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES  
            Account.h
)