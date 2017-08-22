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
  
  
data structure
------

Class Name      | Description
----------------|------------------------
NgxArray        | wrapper for nginx ngx_array_t.
NgxList         | wrapper for nginx ngx_list_t.
NgxQueue        | wrapper for nginx ngx_queue_t.
NgxBuf          | wrapper for nginx ngx_buf_t.
NgxChain        | wrapper for nginx ngx_chain_t.
NgxRbtree       | wrapper for nginx ngx_rbtree_t.


