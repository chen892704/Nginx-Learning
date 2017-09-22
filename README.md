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

-----------  
  
**module**    
  
http/test  设计文档
    
- 模块名：	ndg_test_module
- 配置指令：ndg_test on|off		开关模块功能只能在 location里配置
- 使用 ngx_command_t 和相关函数解析配置指令
- 使用 ngx_http_module_t 定义功能函数，创建配置数据并初始化
- 使用 ngx_module_t 定义模块
- 不直接处理 HTTP 请求，只在 URL 重写阶段里执行
- 根据配置指令的 on|off 决定输出字符串的内容
- 编写 config 脚本，通过 "--add-module" 静态链接选项集成进 Nginx
- 为了简单起见，所有代码实现都在 ModNdgTest.cpp 
