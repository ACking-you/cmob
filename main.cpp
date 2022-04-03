
#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <glog/logging.h>
#include "../BenchMark/Timer.h"


#define JSON_FILENAME "config_src.json"
#define CMAKE_FILENAME "CMakeLists.txt"
namespace fs = std::filesystem;
namespace nl = nlohmann;

struct configPath{
    fs::path exe_path;
    fs::path cur_path;
}path_info;

enum class command{
    LIST=1,
    ADD,
    GET,
    REMOVE,
    CLEAR,
    SHOW
};

using cm = command;
std::map<std::string ,cm>mapping{
        {"add",cm::ADD},
        {"list",cm::LIST},
        {"get",cm::GET},
        {"remove",cm::REMOVE},
        {"clear",cm::CLEAR},
        {"show",cm::SHOW}
};
std::unordered_map<std::string,std::string>objPath_mapping;

//定义一个json读写类，方便RAII进行持久化
class JsonUtil{
fs::path json_path;
void printError(int state_code){
    LOG(ERROR)<<"json error:";
    switch (state_code) {
        case 0:
            LOG(ERROR)<<"read from:"<<json_path<<"\n  error occur!";
            break;
        case 1:
            LOG(ERROR)<<"write from:"<<json_path<<"\n  error occur!\n";
            break;
        default:
            LOG(ERROR)<<"error occur,but I don't know what happened!\n";
    }
}

public:
    explicit JsonUtil(std::string_view path):json_path(std::string(path)){
        json_path/=JSON_FILENAME;
        read();
    }

    static int readFromJson(fs::path const& read_path){
        LOG(INFO) << "start read json_file";
        
        nl::json j;
        if (std::ifstream ifs(read_path);ifs) {
            ifs>>j;
            objPath_mapping = std::move(j["json"].get<std::unordered_map<std::string,std::string>>());
        }else{
            return -1;
        }
        return 0;
    }

    static int writeToJson(fs::path const & writeTo_path){
        nlohmann::json j;
        j["json"] = objPath_mapping;
        if(std::ofstream ofs(writeTo_path);ofs){
            ofs<<j.dump(4);
        }else{
            return -1;
        }
        return 0;
    }

    void read(){
        if(readFromJson(json_path)==-1){
            printError(0);
        }
        else
        {
            LOG(INFO)<<"read json_file successful!";
        }
    }
    void write(){
        if (writeToJson(json_path) == -1) {
            printError(1);
        }else{
            LOG(INFO)<<"write json_file successful!";
        }
    }
};



void initPath(const fs::path& exe_path){
    //LOG(INFO)<<"initPath arg:"<<exe_path;
    path_info.cur_path =  fs::current_path();
    //LOG(INFO)<<"cur_path:"<<path_info.cur_path;
    path_info.exe_path = exe_path.parent_path();
    //LOG(INFO)<<"exe_path:"<<path_info.exe_path;
}

void printHelp(){
    std::cout<<"use: cmob [Commands] [args]\n\n";
    std::cout<<"Commands:\n";
    for (auto&&[k,v]: mapping) {
        std::cout<<k<<'\n';
    }
}

void doRemove(const char *template_name);

void doList();

int doCreat(const char* template_name);

int invoke_get(std::string_view src);

void doGet(const char* template_name);


void doAdd(const char *folderame);

void remove_folder(const fs::path & folder);

void PrintClearHelper();

void doShow(const char *string);

int main(int argc , char* argv[]) {
    if(argc<2){
        printHelp();
        return 0;
    }
    Timer timer;

    auto it = mapping.find(argv[1]);
    command opt;
    if(it==mapping.end()){
        opt = command(0);
    }else {
        opt = it->second;
    }

    google::InitGoogleLogging(argv[0]);
    initPath(argv[0]);
    auto log_path = (path_info.exe_path/"log").string();
    if(!fs::exists(log_path)){//不存在则创建log文件夹
        fs::create_directory(log_path);
    }
    //全局日志配置：如果是执行clear清除日志库的命令，那么把当前日志库定向到系统的temp目录，防止删除文件不成功
    FLAGS_log_dir = opt==cm::CLEAR?fs::temp_directory_path().string(): log_path;
    FLAGS_alsologtostderr = false;


    LOG(INFO)<<"set log path:"<<log_path;
    LOG(INFO)<<"is log file switch ok?"<<FLAGS_log_dir;
    JsonUtil jsonUtil(move(path_info.exe_path.string()));


    switch (opt) {
        case cm::LIST:
            if(argc!=2){
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            LOG(INFO)<<"list command start...";
            doList();
            std::cout<<"LIST exec ";
            break;
        case cm::ADD:
            LOG(INFO)<<"add command start...";
            if(argc!=3){
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            if(doCreat(argv[2])==-1){
                LOG(ERROR)<<"add error,no CMakeLists.txt exist!\npath:"<<path_info.cur_path;
            }else{
                jsonUtil.write();
                std::cout<<"CREATE exec ";
            }
            break;
        case cm::GET:
            if(argc!=3){
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            LOG(INFO)<<"get command start...";
            doGet(argv[2]);
            std::cout<<"GET exec ";
            break;
        case cm::REMOVE:
            if (argc != 3) {
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            LOG(INFO)<<"remove command start...";
            doRemove(argv[2]);
            jsonUtil.write();
            std::cout<<"REMOVE exec ";
            break;
        case cm::CLEAR :
            if(argc!=2&&argc!=3){
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            LOG(INFO)<<"clear command start...";
            doAdd(argc == 3 ? argv[2] : nullptr);
            jsonUtil.write();
            std::cout<<"CLEAR exec ";
            break;
        case cm::SHOW:
            if(argc!=3){
                printHelp();
                std::cout<<"\n\nexec  ";
                break;
            }
            LOG(INFO)<<"show command start...";
            doShow(argv[2]);
            std::cout<<"SHOW exec ";
            break;
        default:
            printHelp();
            std::cout<<"\n\nexec  ";
    }
    google::ShutdownGoogleLogging();
    return 0;
}

void doShow(const char *template_name) {
    auto it = objPath_mapping.find(template_name);
    if(it!=objPath_mapping.end()){
        std::cout<<"\n\n"<<it->second;
    }else{
        LOG(WARNING)<<"template name not exist";
        std::cout<<"template name not exist\n";
    }
}


void doAdd(const char *folder) {
    if(folder == nullptr){
        PrintClearHelper();
        std::cout<<"you remove "<<objPath_mapping.size()<<" template file successful!\n";
        objPath_mapping.clear();
    } else{
        do{
            auto rm_path = path_info.exe_path;
            if (strcmp(folder, "log") == 0) {
                rm_path/="log";
                remove_folder(rm_path);
                break;
            }
            PrintClearHelper();
        }while (false);
    }
}

void PrintClearHelper() {
    printf("more clear option:\n");
    printf("log :to remove all log files\n \n\n");
}

void remove_folder(const fs::path &folder) {//TODO 由于删除的是日志库，而日志在启动时持有对应的文件描述符，将导致文件无法删除
    std::error_code errc;
    auto n = fs::remove_all(folder,errc);
    if(errc){
        LOG(WARNING)<<"remove_folder error";
        std::cerr<<"remove_folder error\nin path:"<<folder<<'\n';
    }else{
        LOG(INFO)<<"remove "<<n<<" files ok!";
        std::cout<<"remove"<<n<<" files ok!\n";
    }
}

void doRemove(const char *template_name) {
    auto ret = objPath_mapping.erase(template_name);
    if(ret == 0){
        LOG(WARNING)<<"template name not exist";
        std::cerr<<"template name not exist!\n";
    }
}

void doList() {
    LOG(INFO)<<"list exec:template_name:";

    std::cout<<"you have "<<objPath_mapping.size()<<" template\n"<<"template_name:\n";
    for (auto&& [k,v]: objPath_mapping) {
        LOG(INFO)<<k;
        std::cout<<k<<'\n';
    }
}

int doCreat(const char *template_name) {
    if(!is_directory(path_info.exe_path)){
        return -1;
    }
    fs::path src_path;
    for (const auto &item:  fs::directory_iterator(path_info.cur_path)) {
        do {
            if (!item.is_regular_file())
                break;
            if (item.path().filename() != CMAKE_FILENAME)
                break;
            src_path = item.path();
            goto end;
        } while (true);
    }
    end:
    if(src_path.empty())return -1;

    std::string  cmake_src;
    if(std::ifstream ifs(src_path);ifs){
        std::string tmp;
        while (std::getline(ifs, tmp)) {
            tmp.push_back('\n');
            cmake_src.append(tmp);
        }
    }else{
        return -1;
    }
    //TODO 暂时不持久化到磁盘，最终程序结束再持久化到磁盘
    objPath_mapping[template_name] = cmake_src;//更新mapping的资源
    return 0;
}

int invoke_get(std::string_view src) {
    auto obj_path = path_info.cur_path/CMAKE_FILENAME;
    if (std::ofstream ofs(obj_path);ofs) {
        ofs<<src;
    }else{
        return -1;
    }
    return 0;
}

void doGet(const char *template_name) {
    LOG(INFO)<<"get command exec...";
    int state = -2;
    for (auto&&[k,v]: objPath_mapping) {
        do {
            if(k!=template_name){
                break;
            }
            state = invoke_get(v);
            goto end;
        }while(true);
    }
    end:
    //错误打印处理
    switch (state)
    {
        case -2:
            LOG(ERROR) << "get failed,  template name don't exist!";
            std::cerr <<  "get failed,  template name don't exist!\n";
            break;
        case -1:
            LOG(ERROR) << "get failed , file path error";
            std::cerr <<"get failed , file path error\n";
            break;
        case 0:
            LOG(INFO) << "get successful!";
            std::cerr << "get successful!\n";
            break;
        default:
            break;
    }
}
