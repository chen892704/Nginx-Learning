#include <iostream>
#include "NgxAll.hpp"

struct NdgTestConf final
{
	ngx_flag_t enabled = ngx_nil;			// 标志变量，构造时初始化
};

// 指令数组
static ngx_command_t ndg_test_cmds[] = 			// 配置指令数组
{
	{
		ngx_string("ngd_test"),			// 指令的名字
		NGX_HTTP_LOC_CONF | NGX_CONF_FLAG,	// 指令的作用域和类型
		ngx_conf_set_flag_slot,			// 解析函数指针
		NGX_HTTP_LOC_CONF_OFFSET,		// 数据的存储位置
		offsetof(NdgTestConf, enabled),		// 数据的具体存储变量
		nullptr
	},
	
	ngx_null_command				// 空对象，结束数组
};

static void * create(ngx_conf_t * cf)			// 创建配置数据结构
{
	return NgxPool(cf).alloc<NdgTestConf>();	// 由内存池分配内存，构造对象
}

// 读取配置参数，根据参数向控制台输出字符串
static ngx_int_t handler(ngx_http_request_t * r)
{
	auto cf = reinterpret_cast<NdgTestConf*>(	// 获取配置数据
		ngx_http_get_module_loc_conf(r, ngd_test_module));
		
	NgxLogError(r).print("hello there");		// 记录运行日志
	
	if(cf->enabled)
	{
		std::cout<<"hello nginx"<<std::endl;
	}
	else
	{
		std::cout<<"hello disabled"<<std::endl;
	}
	
	return NGX_DECLINED;				// 执行成功但未处理
}

// 在Nginx配置解析阶段调用，向Nginx框架注册自己的处理函数
static ngx_int_t init(ngx_conf_t * cf)
{
	auto cmcf = reinterpret_cast<ngx_http_core_main_conf_t*>(
		ngx_http_conf_get_module_main_conf(			// 获取配置结构
				cf, ngx_http_core_module));		// 使用的模块
				
	NgxArray<ngx_http_handler_pt> arr(
		cmcf->phases[NGX_HTTP_REWRITE_PHASE].handlers);		// 该阶段的handler
		
	arr.push(handler);						// 加入自己的handler
	
	return NGX_OK;							// 执行成功
}

static ngx_http_module_t ndg_test_ctx =
{
	nullptr,			// preconfiguration, 解析配置文件前被调用
	init,				// postconfiguration, 解析配置文件后被调用
	nullptr,			// create_main_conf, 创建 http main 域的配置结构
	nullptr,			// init_main_conf, 初始化 http main 域的配置结构
	nullptr,			// create_srv_conf, 创建 server 域的配置结构
	nullptr,			// merge_srv_conf, 合并 server 域的配置结构
	create,				// create_loc_conf, 创建 location 域的配置结构
	nullptr,			// merge_loc_conf, 合并 location 域的配置结构
};

ngx_module_t ndg_test_module =
{
	NGX_MODULE_V1,			// 标准的填充宏
	&ndg_test_ctx,			// 配置功能函数
	ngd_test_cmds,			// 配置指令数组
	NGX_HTTP_MODULE,		// http 模块必需的 tag
	nullptr,			// init master
	nullptr,			// init module
	nullptr,			// init process
	nullptr,			// init thread
	nullptr,			// exit thread
	nullptr,			// exit process
	nullptr,			// exit master
	NGX_MODULE_V1_PADDING		// 标准的填充宏
};

