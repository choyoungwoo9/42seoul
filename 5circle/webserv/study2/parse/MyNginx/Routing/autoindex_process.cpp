#include "../NginxConfig.hpp"


bool get_file_list(string file_path, string &ret)
{
    DIR *dir;
    struct dirent *ent;

    // 현재 디렉토리 열기
    if ((dir = opendir(file_path.c_str())) != NULL) {
        // 디렉토리 내의 파일 읽기
        while ((ent = readdir(dir)) != NULL) {
            // 파일 이름 출력
            ret += ent->d_name;
            ret += "\n";
        }
        // 디렉토리 닫기
        closedir(dir);
        return 1;
    } else {
        // 디렉토리 열기 실패
        // cout << strerror(errno) << endl;
        return 0;
    }
}

void autoindex_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count)
{
    string path = make_path(selected_context.directives.root.path, req.requestTarget);
    if(is_directory(path))
    {
        if(get_file_list(path, res.body))
            return;
        res.code = 403;
    }
    else
        res.code = 404;
    error_page_process(res, req, selected_context, origin_server, redirect_count);
}
