#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"    //不需要按回车确认，scanf和getchar都需要按回车确认
/**
 * @brief 打印前侧格式，为了显示相对居中
 * @author 陈海彬
 * @date 2023/4/29
 */
void format()
{
    printf("\t                                ");
}
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
//写链表
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
}


/**
 * @brief 开始菜单
 * @author 陈海彬
 * @date 2023/4/29
 */
void welcome()
{
    system("cls");
    printf("\n\n\n\n\n\n\n");
    format();
    printf("——————————————————————————————————————————\n");
    format();
    printf("|    欢迎使用重庆邮电大学学生管理系统    |\n");
    format();
    printf("——————————————————————————————————————————\n");
    format();
    printf("|             请选择功能列表             |\n");
    format();
    printf("|             1.录入学生信息             |\n");
    format();
    printf("|             2.浏览学生信息             |\n");
    format();
    printf("|             3.查找学生信息             |\n");
    format();
    printf("|             4.删除学生信息             |\n");
    format();
    printf("|             5.修改学生信息             |\n");
    format();
    printf("|             6.学生排序显示             |\n");
    format();
    printf("|             0.退出系统                 |\n");
    format();
    printf("——————————————————————————————————————————\n");
    //format();
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
void bubbleSort(struct Node* headNode)
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
/**
 * @brief 按键交互
 * @author 陈海彬
 * @date 2023/4/29
 */
void keyDown()
{
    struct Student data;//临时存储信息
    struct Node* result = NULL;//定义临时指针存储查找结果
    char userKey = getch();//不需要按回车确认，scanf和getchar都需要按回车确认
    format();
    switch (userKey)
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
            //暂停
            system("pause");
            //清屏
            system("cls");
            saveInfoToFile(list, "Student.txt");
            break;
        case '2':
            //浏览学生信息
            printList(list);
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
            bubbleSort(list);
            printList(list);
            break;

        case '0':
            /**
            * @brief 退出系统
            * @author 陈海彬
            * @date 2023/4/29
            */
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            format();
            printf("感谢使用重庆邮电大学学生管理系统\n");
            format();
            printf("欢迎再次使用，拜拜！\n");
            system("pause");
            exit(0);
            break;
        default:
            printf("输入有误，请重新输入！\n");
            //format();
            break;
    }

}

int main()
{
    list = createList();
    readInfoFromFile(list, "Student.txt");
    while(1)
    {
        welcome();
        keyDown();
        system("pause");
        system("cls");
    }
    getchar();
    return 0;
}
