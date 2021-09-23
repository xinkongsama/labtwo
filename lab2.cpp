#include<bits/stdc++.h>
using namespace std;

FILE *pfin;
char fsm[7][256];

class CodeTest
{
    public:
        CodeTest(){}
        void Devide();
        void Allcount(string str);
        void print(int level);
        void Delete(char fsm[7][256]);
    private:
        int ch;
        int state = 0;
        int keyword = 0, switch_else_num[100] = {0}, switch_num = 0, flag = 0;
        int if_else_count = 0, if_elseif_else_count = 0, flag2 = 0, flag3 = 0;
        string danci, mark;
        stack <int> ifelse_stack;
};

void CodeTest::Allcount(string str)
{
	if (str == "auto" || str == "break" || str == "case" || str == "char"
    || str == "const" || str == "continue" || str == "default" || str == "do"
    || str == "double" || str == "else" || str == "enum" || str == "extern"
    || str == "float" || str == "for" || str == "goto" || str == "if"
    || str == "int" || str == "long" || str == "register" || str == "return"
    || str == "short" || str == "signed" || str == "sizeof" || str == "static"
    || str == "struct"|| str == "switch" || str == "typedef" || str == "union"
    || str == "unsigned" || str == "void" || str == "volatile" || str == "while")
    {
        keyword++;
        if (str == "switch")
        {
            flag = 1;
            switch_num++;
        }
        if (str == "case" && flag == 1)
        {
            switch_else_num[switch_num]++;
        }
        if (str == "default" && flag == 1)
        {
            flag = 0;
        }
        if (str == "if")
        {
            ifelse_stack.push(-1);
            ifelse_stack.push(1);
        }
        if (str == "else")
        {
            flag2 = 0;
            flag3 = 0;
            while (ch == ' ' || ch == 10)  // 跳过空格和换行符
            {
                ch = fgetc(pfin);
            }
            if (ch == 'i')
            {
                mark = "";
                mark += ch;
                ch = fgetc(pfin);
                mark += ch;
                if (mark == "if")
                {
                    keyword++;
                    ifelse_stack.push(1);
                    flag2 = 1;
                }
            }
            else if (ch == 123)
            {
                flag3 = 1;
            }
            if (flag2 == 0)
            {
                int ifelse_stack_count = 0;
                while (ifelse_stack.top() > 0 && !ifelse_stack.empty())
                {
                    ifelse_stack_count += ifelse_stack.top();
                    ifelse_stack.pop();
                }
                if (ifelse_stack_count > 1)
                {
                    if_elseif_else_count++;
                }
                else if (ifelse_stack_count == 1)
                {
                    if_else_count++;
                }
                if (flag3 == 1)
            	{
                	ifelse_stack.push(0);
            	}
            }
        }
    }
}

void CodeTest::print(int level)
{
    if(level >= 1)
    {
        cout << "total num: " << keyword << endl;
    }
    if(level >= 2)
    {
        cout << "switch num: " << switch_num << endl;
        cout << "case num:";
        if (switch_num == 0)
        {
            cout << " 0";
        }
        else
        {
            for (int i = 1; i <= switch_num; i++)
            {
                cout << " " << switch_else_num[i];
            }
        }
        cout << endl;
    }
    if(level >= 3)
    {
        cout << "if-else num: " << if_else_count << endl;
    }
    if(level >= 4)
    {
        cout << "if-elseif-else num: " << if_elseif_else_count << endl;
    }
}

void CodeTest::Delete(char fsm[7][256])
{
    int lenth = sizeof(char) * 256;
    memset(fsm[0], 0, lenth);
    memset(fsm[1], 0, lenth);
    memset(fsm[2], 2, lenth);
    memset(fsm[3], 3, lenth);
    memset(fsm[4], 3, lenth);
    memset(fsm[5], 5, lenth);
    memset(fsm[6], 5, lenth);
    fsm[0]['"'] = 5;
    fsm[0]['/'] = 1;
    fsm[1]['/'] = 2;
    fsm[1]['*'] = 3;
    fsm[2]['\n'] = 7;
    fsm[3]['*'] = 4;
    fsm[4]['/'] = 7;
    fsm[5]['\\'] = 6;
    fsm[5]['"'] = 0;
}

void CodeTest::Devide()
{
    while ((ch=fgetc(pfin)) != EOF)
    {
        state = fsm[state][ch];
        switch (state)
        {
            case 5:
            case 6:
            case 0:
            if (ch == '"')  // 忽略双引号
            {
                ch = fgetc(pfin);
                while (ch != '"')
                {
                    ch = fgetc(pfin);
                }
                continue;
            }
            if (ch == 39)  // 忽略单引号
            {
                ch = fgetc(pfin);
                while (ch != 39)
                {
                    ch = fgetc(pfin);
                }
                continue;
            }
            if (ch == ' ' || ch == 10)  // 忽略空格和换行符
            {
                continue;
            }
            if (ch == '{')
            {
                ifelse_stack.push(0);
            }
            if (ch == 125)
            {
                while (ifelse_stack.top() != 0)
                {
                    ifelse_stack.pop();
                }
                ifelse_stack.pop();
            }
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))  // 发现一个单词
            {
                danci = "";
                while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
                              || (ch == '_') || (ch == '/') || (ch == '.'))
                {
                    if (ch >= 'A' && ch <= 'Z')
                    {
                        ch += 32;  // 转换成小写
                    }
                    danci += ch;  // 把当前字母存入该单词的数组
                    ch = fgetc(pfin);
                }  // 一个单词结束
                Allcount(danci);
            }
            case 7:
            state = 0;
            break;
        }
    }
}

int main()
{
    CodeTest *t = new CodeTest();
    int level;
    char filename[100];
    cout<<"路径：";
    gets(filename);
    cout<<"等级：";
    cin>>level;
    if ((pfin=fopen(filename,"r"))==NULL)
    {
        cout << "文件打开错误";
        return 0;
    }
    t->Delete(fsm);
    t->Devide();
    fclose(pfin);
    t->print(level);
    return 0;
}
