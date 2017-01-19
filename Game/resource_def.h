const char* str_map[]=
{
    "金币","Cash",//0
    "买入A","Buy A",//1
    "买入B","Buy B",//2
    "卖出A","Sell A",//3
    "卖出B","Sell B",//4
    "下一天","Next Day",//5
    "退出","Exit",//6
    "游戏结束","Game End.",//7
    "再来一次","Restart",//8
    "退出游戏","Exit",//9
    "A价格","A Price",//10
    "B价格","B Price",//11
    "拥有A","Have A",
    "拥有B","Have B",

    "LAST_STRING"
};
const char* lang_name[]=
{
    "中文(简体)",
    "English(US)",

    "LAST_STRING"
};

#define LANG_ALL 2

#define LANG_zh_CN 0
#define LANG_en_US 1

int lang=LANG_zh_CN;

const char* getstr(int id)
{
    return str_map[id*LANG_ALL+lang];
}
