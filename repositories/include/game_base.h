#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "repository_export.h"
#include <string>

namespace Games {

// 游戏状态枚举
enum class game_status {
    k_not_started,  // 未开始
    k_playing,      // 进行中
    k_paused,       // 已暂停
    k_finished,     // 已结束
    k_quit          // 已退出
};

// 游戏基类接口
class REPOSITORY_API game_base {
public:
    virtual ~game_base() = default;
    
    // 获取游戏名称
    virtual std::string get_name() const = 0;
    
    // 获取游戏描述
    virtual std::string get_description() const = 0;
    
    // 初始化游戏（设置参数等）
    virtual void initialize() = 0;
    
    // 重置游戏
    virtual void reset() = 0;
    
    // 运行游戏主循环
    virtual void run() = 0;
    
    // 获取游戏状态
    virtual game_status get_status() const = 0;
    
    // 检查游戏是否结束
    virtual bool is_finished() const = 0;
};

} // namespace Games

#endif // GAME_BASE_H

