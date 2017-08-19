# Nginx-Learning  
Nginx development：Use C++ and boost libraries  

common tools
------
Class Name      | Description
----------------|------------------------
NgxUnsetValue   | generic unset value -1.
NgxValue        | wrapper for nginx int, include init/merge/unset.
NgxException    | wrapper for nginx error code.
NgxPool         | wrapper for nginx memory pool.
NgxAlloctor     | adapter to C++ allocator.
NgxString       | wrapper for nginx ngx_str_t.
NgxClock        | wrapper for nginx time functions.
NgxDatetime     | wrapper for nginx date functions.
NgxLog          | wrapper for nginx error log.

