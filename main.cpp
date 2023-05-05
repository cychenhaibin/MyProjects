#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "conio.h"    //不需要按回车确认，scanf和getchar都需要按回车确认
void regist();
void login();
void welcome();
void keykeyDown();
void keyDown();
//int flag=0;
/**
 * @brief 打印前侧格式，为了显示相对居中
 * @author 陈海彬
 * @date 2023/4/29
 */
void format()
{
    printf("\t                               ");
}
void pattern()
{
    printf("|                                            |\n");
}
/**
 * @brief 对format和printf()再次封装，按格式打印一个字符串
 * @author 陈海彬
 * @date 2023/5/2
 */
void format_p(char *str){
    format();
    printf(str);
}
/**
 * @brief 用户结构体
 * @author 陈海彬
 * @date 2023/5/2
 */
typedef struct user
{
    char name[20];//用户名
    char password[20];//密码
}USER;

struct userLink{//用户链表
    struct user data;
    struct userLink *next;
};

/**
 * @brief 学生结构体
 * @author 陈海彬
 * @date 2023/4/29
 */
struct Student
{
    //学生姓名 年龄 年级 学历 录取分数 身高 体重 院系 生源地
    char name[10];     //姓名
    int age;           //年龄
    int grade;         //年级
    char education[10];//学历
    int score;         //录取分数
    int height;        //身高
    float weight;      //体重
    char college[50];  //院系
    char ofStudent[20];//生源地
};
//学生链表
struct Node
{
    struct Student data;
    struct Node* next;
};
struct Node* list = NULL;
//创建链表->用第一个结点表示整个链表
//创建一个结构体变量
struct Node* createList()
{
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    //变量使用前要初始化
    //做的是有表头的链表，要差异化处理
    headNode->next = NULL;
    return headNode;
}

void startInfo(){
    system("cls");
    printf("\n\n\n\n");
    format();
    printf("——————————————————————————————————————\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|  欢迎来到重庆邮电大学学生管理系统  |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|               1.注册               |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|               2.登录               |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|               0.退出               |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("|      请输入对应的数字进入功能！    |\n");
    format();
    printf("|                                    |\n");
    format();
    printf("——————————————————————————————————————\n");
    //format();
    keykeyDown();
    format();
    /*int n;
    while (scanf_s("%d",&n)!=1 || !(n==1||n==2||n==0))
    {
        format();
        printf("输入有误,请重新输入\n");
        format();
        fflush(stdin);//清除缓存区
    }
    switch (n)
    {
        case 1:regist();
            break;
        case 2:login();
            break;
        case 0:
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            format();
            printf("感谢使用重庆邮电大学学生管理系统\n");
            format();
            printf("欢迎再次使用，拜拜！\n");
            system("pause");
            exit(0);
            break;
    }*/
}
void keykeyDown()
{
    format();
    char userKey = getch();//不需要按回车确认，scanf和getchar都需要按回车确认
    switch (userKey)
    {
        case '1':
            regist();
            break;
        case '2':
            login();
            break;
        case '0':
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            format();
            printf("感谢使用重庆邮电大学学生管理系统\n");
            format();
            printf("欢迎再次使用，拜拜！\n");
            format();
            system("pause");
            exit(0);
            break;
        default:
            //format();
            printf("输入有误,请重新输入\n");
            format();
            system("pause");
            startInfo();
            fflush(stdin);//清除缓存区
    }
}

void regist(){
    USER oldUser;
    USER newUser;
    char name[20];
    system("cls");
    format();
    printf("请输入您要注册的用户名:\n");
    format();
    scanf("%s",name);
    FILE* fd = NULL;
    fd = fopen("UserList.txt","rb");//打开账号文件
    while (fread(&oldUser,sizeof(USER),1,fd))//如果读到数据，则判断用户名是否一致
    {
        if (strcmp(oldUser.name,name)==0)
        {
            //如果输入用户名在列表中存在
            format();
            printf("该用户名存在，请重新输入！！！\n");
            format();
            scanf("%s",name);
            fseek(fd,0,SEEK_SET);//将文件指针重新定位到开头
        }
    }
    fclose(fd);
    fd = NULL;
    //全部检索完，添加用户
    strcpy(newUser.name,name);
    format();
    printf("请设置您的密码:\n");
    format();
    scanf("%s",newUser.password);
    format();
    FILE* fw = NULL;
    fw = fopen("UserList.txt","ab");
    fwrite(&newUser,sizeof(USER),1,fw);//用户信息写入文件
    fclose(fw);
    fw = NULL;
    //format();
    printf("注册完成\n");
    format();
    system("pause");
    system("cls");
    startInfo();//回到开始界面
    system("pause");
    //flag=1;
}


/**
 * @brief 登录模块
 * @author 陈海彬
 * @date 2023/5/2
 */

void login(){
    system("cls");
    USER userTemp;//读取用户
    format_p("请输入您的用户名:\n");
    char name[20],password[20];
    format();
    scanf("%s",name);
    int index = 0;//用来记录是账户库中第几个用户
    FILE* fd = NULL;
    fd = fopen("UserList.txt","rb");//打开账号文件
    while (fread(&userTemp,sizeof(USER),1,fd))//如果读到数据，则判断用户名是否一致
    {
        index++;//每读一个，记录+1
        if (strcmp(userTemp.name,name)==0)
        {
            //如果输入用户名在列表中存在
            format_p("请输入密码:\n");
            int count = 0;//输入次数
            do
            {
                format();
                scanf("%s",password);
                count++;
                if (strcmp(userTemp.password,password)==0)//密码正确
                {
                    fclose(fd);//释放资源
                    fd = NULL;
                    welcome();
                    //flag=0;
                    return;//密码正确这函数后面无用
                }
                else if(count<=3)
                {//密码错误
                    format_p("密码错误！！！\n");
                    format();
                    printf("请重新输入:(你还有%d次机会!)\n",3-count);
                }
                else
                {//输入次数用完
                    format_p("密码错误！！!,即将回到主界面\n");
                    format();
                    system("pause");
                    startInfo();
                    //flag=1;
                }
            } while (1);//最多允许输入3次
        }
    }
    fclose(fd);
    fd = NULL;
    //该用户不存在，提示，并返回主界面
    format_p("该用户不存在！！！，即将回到主界面\n");
    format();
    system("pause");
    startInfo();
    //flag=1;
}

/**
 * @brief 开始菜单
 * @author 陈海彬
 * @date 2023/4/29
 */
void welcome()
{
    system("cls");
    printf("\n\n\n");
    format();
    printf("——————————————————————————————————————————————\n");
    format();
    pattern();
    format();
    printf("|      欢迎使用重庆邮电大学学生管理系统      |\n");
    format();
    //printf("——————————————————————————————————————————\n");
    pattern();
    format();
    printf("|               请选择功能列表               |\n");
    format();
    pattern();
    format();
    printf("|               1.录入学生信息               |\n");
    format();
    pattern();
    format();
    printf("|               2.浏览学生信息               |\n");
    format();
    pattern();
    format();
    printf("|               3.查找学生信息               |\n");
    format();
    pattern();
    format();
    printf("|               4.删除学生信息               |\n");
    format();
    pattern();
    format();
    printf("|               5.修改学生信息               |\n");
    format();
    pattern();
    format();
    printf("|               6.学生排序显示               |\n");
    format();
    pattern();
    format();
    printf("|               0.退出管理系统               |\n");
    format();
    pattern();
    format();
    printf("|         请输入对应数字进入相应功能         |\n");
    format();
    pattern();
    format();
    printf("——————————————————————————————————————————————\n");
    keyDown();
}

/**
 * @brief 创建节点->把用户输入的数据变成节点
 * @author 陈海彬
 * @date 2023/4/29
 */
struct Node* createNode(struct Student data)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
/**
 * @brief 表头插入
 * @author 陈海彬
 * @date 2023/4/29
 */
void insertByHead(struct Node* headNode, struct Student data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

/**
 * @brief 删除方式
 * @author 陈海彬
 * @date 2023/4/29
 */
void deleteByName(struct Node* headNode, char *posName)
{
    struct Node* posFrontNode = headNode;
    struct Node* posNode = headNode->next;
    //找指定位置
    while (posNode != NULL && strcmp(posNode->data.name,posName))
    {
        posFrontNode = posNode;
        posNode = posFrontNode->next;
    }
    if (posNode == NULL)
    {
        return;
    }
    //不为NULL，找到就可以做删除
    posFrontNode->next = posNode->next;
    free(posNode);
    posNode = NULL;
}

/**
 * @brief 查找方式
 * @author 陈海彬
 * @date 2023/4/29
 */
struct Node* searchByName(struct Node* headNode, char *posName)
{
    struct Node* pMove = headNode->next;
    while (pMove != NULL && strcmp(pMove->data.name,posName))
    {
        pMove = pMove->next;
    }
    return pMove;
}

/**
 * @brief 打印节点
 * @author 陈海彬
 * @date 2023/4/29
 */
void printList(struct Node* headNode)
{
    system("cls");
    struct Node* pMove = headNode->next;//因为有表头
    printf("\t");
    printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    printf("\t");
    printf("|                                         重庆邮电大学学生信息展示                                      |\n");
    printf("\t");
    printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    printf("\t");
    printf("|姓名\t年龄\t年级\t学历\t录取分数\t身高\t体重\t院系\t\t\t\t生源地\t|\n");
    while (pMove != NULL)
    {
        printf("\t|%s\t%d\t%d\t%s\t%d\t\t%d\t%.2f\t%s\t\t\t%s\t|\n",
               pMove->data.name,
               pMove->data.age,
               pMove->data.grade,
               pMove->data.education,
               pMove->data.score,
               pMove->data.height,
               pMove->data.weight,
               pMove->data.college,
               pMove->data.ofStudent
        );
        pMove = pMove->next;
    }
    printf("\t");
    printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
    format();
}



/**
 * @brief 把链表中的内容写到文件中
 * @author 陈海彬
 * @date 2023/4/29
 */
void saveInfoToFile(struct Node* headNode, char *fileName)
{
    //定义一个文件指针，打开文件
    FILE *fp = fopen(fileName, "w");
    //判NULL处理
    //fprintf 格式化读写
    struct Node* pMove = headNode->next;
    while (pMove != NULL)
    {
        fprintf(fp, "%s\t%d\t%d\t%s\t%d\t\t%d\t%.2f\t%s\t\t\t%s\n",
                pMove->data.name,
                pMove->data.age,
                pMove->data.grade,
                pMove->data.education,
                pMove->data.score,
                pMove->data.height,
                pMove->data.weight,
                pMove->data.college,
                pMove->data.ofStudent
        );
        pMove = pMove->next;
    }
    //关闭文件
    fclose(fp);
}

/**
 * @brief 第一次需要把文件中的内容读到链表中去
 * @author 陈海彬
 * @date 2023/4/29
 */
void readInfoFromFile(struct Node* headNode, char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    //判NULL处理
    if (fp == NULL)//刚开始读的时候缓存文件不存在
    {
        //具有创建的形式打开文件
        fp = fopen(fileName, "w+");//可读可写+创建功能
    }
    //fscanf
    struct Student data;
    while (fscanf(fp, "%s\t%d\t%d\t%s\t%d\t\t%d\t%f\t%s\t\t\t%s\n",
                  data.name,
                  &data.age,
                  &data.grade,
                  data.education,
                  &data.score,
                  &data.height,
                  &data.weight,
                  data.college,
                  data.ofStudent) != EOF)//EOF文件结束标记-1
    {
        insertByHead(headNode, data);
    }
    //关闭文件
    fclose(fp);
}

/**
 * @brief 链表冒泡排序1.扫描所有数据2.相邻的元素相互比较
 * @author 陈海彬
 * @date 2023/4/29
 */
void bubbleSortAge(struct Node* headNode)
{
    struct Node* firstNode = headNode->next;
    struct Node* secondNode = headNode;
    while (firstNode != NULL)
    {
        while (firstNode->next != NULL)
        {
            if (firstNode->data.age>firstNode->next->data.age)
            {
                //只需要交换节点的数据
                struct Student tempData;
                tempData= firstNode->data;
                firstNode->data = firstNode->next->data;
                firstNode->next->data = tempData;
            }
            firstNode = firstNode->next;
        }
        firstNode = secondNode->next;
        secondNode = firstNode;
    }
}
void bubbleSortGrade(struct Node* headNode)
{
    struct Node* firstNode = headNode->next;
    struct Node* secondNode = headNode;
    while (firstNode != NULL)
    {
        while (firstNode->next != NULL)
        {
            if (firstNode->data.grade>firstNode->next->data.grade)
            {
                //只需要交换节点的数据
                struct Student tempData;
                tempData= firstNode->data;
                firstNode->data = firstNode->next->data;
                firstNode->next->data = tempData;
            }
            firstNode = firstNode->next;
        }
        firstNode = secondNode->next;
        secondNode = firstNode;
    }
}
void bubbleSortScore(struct Node* headNode)
{
    struct Node* firstNode = headNode->next;
    struct Node* secondNode = headNode;
    while (firstNode != NULL)
    {
        while (firstNode->next != NULL)
        {
            if (firstNode->data.score<firstNode->next->data.score)
            {
                //只需要交换节点的数据
                struct Student tempData;
                tempData= firstNode->data;
                firstNode->data = firstNode->next->data;
                firstNode->next->data = tempData;
            }
            firstNode = firstNode->next;
        }
        firstNode = secondNode->next;
        secondNode = firstNode;
    }
}
void bubbleSortHeight(struct Node* headNode)
{
    struct Node* firstNode = headNode->next;
    struct Node* secondNode = headNode;
    while (firstNode != NULL)
    {
        while (firstNode->next != NULL)
        {
            if (firstNode->data.height>firstNode->next->data.height)
            {
                //只需要交换节点的数据
                struct Student tempData;
                tempData= firstNode->data;
                firstNode->data = firstNode->next->data;
                firstNode->next->data = tempData;
            }
            firstNode = firstNode->next;
        }
        firstNode = secondNode->next;
        secondNode = firstNode;
    }
}
void bubbleSortWeight(struct Node* headNode)
{
    struct Node* firstNode = headNode->next;
    struct Node* secondNode = headNode;
    while (firstNode != NULL)
    {
        while (firstNode->next != NULL)
        {
            if (firstNode->data.weight>firstNode->next->data.weight)
            {
                //只需要交换节点的数据
                struct Student tempData;
                tempData= firstNode->data;
                firstNode->data = firstNode->next->data;
                firstNode->next->data = tempData;
            }
            firstNode = firstNode->next;
        }
        firstNode = secondNode->next;
        secondNode = firstNode;
    }
}
/**
 * @brief 按键交互
 * @author 陈海彬
 * @date 2023/4/29
 */
void keyDown()
{
    struct Student data{};//临时存储信息
    struct Node* result = NULL;//定义临时指针存储查找结果
    format();
    char studentKey = getch();//不需要按回车确认，scanf和getchar都需要按回车确认
    switch (studentKey)
    {
        case '1':
            /**
            * @brief 添加学生信息
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("请输入学生姓名:\n");
            format();
            scanf("%s",data.name);

            format();
            printf("请输入学生年龄:\n");
            format();
            scanf("%d",&data.age);

            format();
            printf("请输入学生年级:\n");
            format();
            scanf("%d",&data.grade);

            format();
            printf("请输入学生学历:\n");
            format();
            scanf("%s",data.education);

            format();
            printf("请输入录取成绩:\n");
            format();
            scanf("%d",&data.score);

            format();
            printf("请输入学生身高:\n");
            format();
            scanf("%d",&data.height);

            format();
            printf("请输入学生体重:\n");
            format();
            scanf("%f",&data.weight);

            format();
            printf("请输入学生学院:\n");
            format();
            scanf("%s",data.college);

            format();
            printf("请输入学生生源地:\n");
            format();
            scanf("%s",data.ofStudent);

            format();
            printf("录入学生信息成功！\n");

            insertByHead(list, data);
            format();
            //暂停
            system("pause");
            //清屏
            system("cls");
            saveInfoToFile(list, "Student.txt");
            break;
        case '2':
            //浏览学生信息
            printList(list);
            //welcome();
            system("pause");
            //welcome();
            break;
        case '3':
            /**
            * @brief 查找学生信息
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("请输入要查找的学生的姓名:\n");
            format();
            scanf("%s",data.name);
            result = searchByName(list, data.name);
            if (result == NULL)
            {
                format();
                printf("查无此人\n");
            }
            else
            {
                printf("\t");
                printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
                printf("\t");
                printf("|姓名\t年龄\t年级\t学历\t录取分数\t身高\t体重\t院系\t\t\t\t生源地\t|\n");
                printf("\t|%s\t%d\t%d\t%s\t%d\t\t%d\t%.2f\t%s\t\t\t%s\t|\n",
                       result->data.name,
                       result->data.age,
                       result->data.grade,
                       result->data.education,
                       result->data.score,
                       result->data.height,
                       result->data.weight,
                       result->data.college,
                       result->data.ofStudent
                );
                printf("\t");
                printf("—————————————————————————————————————————————————————————————————————————————————————————————————————————\n");
            }
            system("pause");
            break;
        case '4':
            /**
            * @brief 删除学生信息
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("请输入要删除的学生的姓名:\n");
            format();
            scanf("%s", data.name);
            format();
            deleteByName(list, data.name);
            printf("操作成功!");
            saveInfoToFile(list, "Student.txt");
            break;
        case '5':
            /**
            * @brief 修改学生信息
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("请输入要修改的学生的姓名:\n");
            format();
            scanf("%s",data.name);
            format();
            result = searchByName(list, data.name);
            if (result == NULL)
            {
                printf("查无此人，无法修改！\n");
                format();
            }
            else
            {
                printf("请输入要修改的信息\n");
                format();
                scanf("%s%d%d%s%d%d%f%s%s",
                      result->data.name,
                      &result->data.age,
                      &result->data.grade,
                      result->data.education,
                      &result->data.score,
                      &result->data.height,
                      &result->data.weight,
                      result->data.college,
                      result->data.ofStudent
                );
                format();
                printf("修改成功！");
                saveInfoToFile(list, "Student.txt");
            }
            break;
        case '6':
            /**
            * @brief 学生排序显示
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            char arr[4];
            format_p("请输入排序方式(年龄/年级/录取分数/身高/体重):\n");
            format();
            scanf("%s",arr);
            if (strcmp(arr, "年龄")==0)
            {
                bubbleSortAge(list);
                printList(list);
                system("pause");
            }
            else if (strcmp(arr, "年级")==0)
            {
                bubbleSortGrade(list);
                printList(list);
                system("pause");
            }
            else if (strcmp(arr, "录取分数")==0)
            {
                bubbleSortScore(list);
                printList(list);
                system("pause");
            }
            else if (strcmp(arr, "身高")==0)
            {
                bubbleSortHeight(list);
                printList(list);
                system("pause");
            }
            else if (strcmp(arr, "体重")==0)
            {
                bubbleSortWeight(list);
                printList(list);
                system("pause");
            }
            else
            {
                format_p("输入错误，请重新输入！");
                system("pause");
            }
            break;

        case '0':
            /**
            * @brief 退出系统
            * @author 陈海彬
            * @date 2023/4/29
            */
            //startInfo();
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            format();
            printf("感谢使用重庆邮电大学学生管理系统\n");
            format();
            printf("欢迎再次使用，拜拜！\n");
            format();
            system("pause");
            exit(0);
            break;
        default:
            printf("输入有误，请重新输入！\n");
            format();
            system("pause");
            fflush(stdin);//清除缓存区
            break;
    }
    //welcome();
}

int main()
{
    list = createList();
    readInfoFromFile(list, "Student.txt");
    startInfo();
    //keykeyDown();
    /*while(flag==1)
    {
        startInfo();
        //keykeyDown();
    }*/
    while(1)
    {
        welcome();
        //keyDown();
        //system("pause");
        system("cls");
    }
    getchar();
    return 0;
}
