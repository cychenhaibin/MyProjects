#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"    //����Ҫ���س�ȷ�ϣ�scanf��getchar����Ҫ���س�ȷ��
/**
 * @brief ��ӡǰ���ʽ��Ϊ����ʾ��Ծ���
 * @author �º���
 * @date 2023/4/29
 */
void format()
{
    printf("\t                                ");
}
/**
 * @brief ѧ���ṹ��
 * @author �º���
 * @date 2023/4/29
 */
struct Student
{
    //ѧ������ ���� �꼶 ѧ�� ¼ȡ���� ��� ���� Ժϵ ��Դ��
    char name[10];     //����
    int age;           //����
    int grade;         //�꼶
    char education[10];//ѧ��
    int score;         //¼ȡ����
    int height;        //���
    float weight;      //����
    char college[50];  //Ժϵ
    char ofStudent[20];//��Դ��
};
//д����
struct Node
{
    struct Student data;
    struct Node* next;
};
struct Node* list = NULL;
//��������->�õ�һ������ʾ��������
//����һ���ṹ�����
struct Node* createList()
{
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    //����ʹ��ǰҪ��ʼ��
    //�������б�ͷ������Ҫ���컯����
    headNode->next = NULL;
    return headNode;
}

/**
 * @brief �����ڵ�->���û���������ݱ�ɽڵ�
 * @author �º���
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
 * @brief ��ͷ����
 * @author �º���
 * @date 2023/4/29
 */
void insertByHead(struct Node* headNode, struct Student data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

/**
 * @brief ɾ����ʽ
 * @author �º���
 * @date 2023/4/29
 */
void deleteByName(struct Node* headNode, char *posName)
{
    struct Node* posFrontNode = headNode;
    struct Node* posNode = headNode->next;
    //��ָ��λ��
    while (posNode != NULL && strcmp(posNode->data.name,posName))
    {
        posFrontNode = posNode;
        posNode = posFrontNode->next;
    }
    if (posNode == NULL)
    {
        return;
    }
    //��ΪNULL���ҵ��Ϳ�����ɾ��
    posFrontNode->next = posNode->next;
    free(posNode);
    posNode = NULL;
}

/**
 * @brief ���ҷ�ʽ
 * @author �º���
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
 * @brief ��ӡ�ڵ�
 * @author �º���
 * @date 2023/4/29
 */
void printList(struct Node* headNode)
{
    system("cls");
    struct Node* pMove = headNode->next;//��Ϊ�б�ͷ
    printf("\t");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("\t");
    printf("|                                         �����ʵ��ѧѧ����Ϣչʾ                                      |\n");
    printf("\t");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("\t");
    printf("|����\t����\t�꼶\tѧ��\t¼ȡ����\t���\t����\tԺϵ\t\t\t\t��Դ��\t|\n");
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
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}


/**
 * @brief ��ʼ�˵�
 * @author �º���
 * @date 2023/4/29
 */
void welcome()
{
    system("cls");
    printf("\n\n\n\n\n\n\n");
    format();
    printf("������������������������������������������������������������������������������������\n");
    format();
    printf("|    ��ӭʹ�������ʵ��ѧѧ������ϵͳ    |\n");
    format();
    printf("������������������������������������������������������������������������������������\n");
    format();
    printf("|             ��ѡ�����б�             |\n");
    format();
    printf("|             1.¼��ѧ����Ϣ             |\n");
    format();
    printf("|             2.���ѧ����Ϣ             |\n");
    format();
    printf("|             3.����ѧ����Ϣ             |\n");
    format();
    printf("|             4.ɾ��ѧ����Ϣ             |\n");
    format();
    printf("|             5.�޸�ѧ����Ϣ             |\n");
    format();
    printf("|             6.ѧ��������ʾ             |\n");
    format();
    printf("|             0.�˳�ϵͳ                 |\n");
    format();
    printf("������������������������������������������������������������������������������������\n");
    //format();
}

/**
 * @brief �������е�����д���ļ���
 * @author �º���
 * @date 2023/4/29
 */
void saveInfoToFile(struct Node* headNode, char *fileName)
{
    //����һ���ļ�ָ�룬���ļ�
    FILE *fp = fopen(fileName, "w");
    //��NULL����
    //fprintf ��ʽ����д
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
    //�ر��ļ�
    fclose(fp);
}

/**
 * @brief ��һ����Ҫ���ļ��е����ݶ���������ȥ
 * @author �º���
 * @date 2023/4/29
 */
void readInfoFromFile(struct Node* headNode, char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    //��NULL����
    if (fp == NULL)//�տ�ʼ����ʱ�򻺴��ļ�������
    {
        //���д�������ʽ���ļ�
        fp = fopen(fileName, "w+");//�ɶ���д+��������
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
                  data.ofStudent) != EOF)//EOF�ļ��������-1
    {
        insertByHead(headNode, data);
    }
    //�ر��ļ�
    fclose(fp);
}

/**
 * @brief ����ð������1.ɨ����������2.���ڵ�Ԫ���໥�Ƚ�
 * @author �º���
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
                //ֻ��Ҫ�����ڵ������
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
 * @brief ��������
 * @author �º���
 * @date 2023/4/29
 */
void keyDown()
{
    struct Student data;//��ʱ�洢��Ϣ
    struct Node* result = NULL;//������ʱָ��洢���ҽ��
    char userKey = getch();//����Ҫ���س�ȷ�ϣ�scanf��getchar����Ҫ���س�ȷ��
    format();
    switch (userKey)
    {
        case '1':
            /**
            * @brief ���ѧ����Ϣ
            * @author �º���
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("������ѧ������:\n");
            format();
            scanf("%s",data.name);

            format();
            printf("������ѧ������:\n");
            format();
            scanf("%d",&data.age);

            format();
            printf("������ѧ���꼶:\n");
            format();
            scanf("%d",&data.grade);

            format();
            printf("������ѧ��ѧ��:\n");
            format();
            scanf("%s",data.education);

            format();
            printf("������¼ȡ�ɼ�:\n");
            format();
            scanf("%d",&data.score);

            format();
            printf("������ѧ�����:\n");
            format();
            scanf("%d",&data.height);

            format();
            printf("������ѧ������:\n");
            format();
            scanf("%f",&data.weight);

            format();
            printf("������ѧ��ѧԺ:\n");
            format();
            scanf("%s",data.college);

            format();
            printf("������ѧ����Դ��:\n");
            format();
            scanf("%s",data.ofStudent);

            format();
            printf("¼��ѧ����Ϣ�ɹ���\n");

            insertByHead(list, data);
            //��ͣ
            system("pause");
            //����
            system("cls");
            saveInfoToFile(list, "Student.txt");
            break;
        case '2':
            //���ѧ����Ϣ
            printList(list);
            break;
        case '3':
            /**
            * @brief ����ѧ����Ϣ
            * @author �º���
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("������Ҫ���ҵ�ѧ��������:\n");
            format();
            scanf("%s",data.name);
            result = searchByName(list, data.name);
            if (result == NULL)
            {
                format();
                printf("���޴���\n");
            }
            else
            {
                printf("\t");
                printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
                printf("\t");
                printf("|����\t����\t�꼶\tѧ��\t¼ȡ����\t���\t����\tԺϵ\t\t\t\t��Դ��\t|\n");
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
                printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
            }
            break;
        case '4':
            /**
            * @brief ɾ��ѧ����Ϣ
            * @author �º���
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("������Ҫɾ����ѧ��������:\n");
            format();
            scanf("%s", data.name);
            format();
            deleteByName(list, data.name);
            printf("�����ɹ�!");
            saveInfoToFile(list, "Student.txt");
            break;
        case '5':
            /**
            * @brief �޸�ѧ����Ϣ
            * @author �º���
            * @date 2023/4/29
            */
            system("cls");
            format();
            printf("������Ҫ�޸ĵ�ѧ��������:\n");
            format();
            scanf("%s",data.name);
            format();
            result = searchByName(list, data.name);
            if (result == NULL)
            {
                printf("���޴��ˣ��޷��޸ģ�\n");
                format();
            }
            else
            {
                printf("������Ҫ�޸ĵ���Ϣ\n");
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
                printf("�޸ĳɹ���");
                saveInfoToFile(list, "Student.txt");
            }
            break;
        case '6':
            /**
            * @brief ѧ��������ʾ
            * @author �º���
            * @date 2023/4/29
            */
            bubbleSort(list);
            printList(list);
            break;

        case '0':
            /**
            * @brief �˳�ϵͳ
            * @author �º���
            * @date 2023/4/29
            */
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
            format();
            printf("��лʹ�������ʵ��ѧѧ������ϵͳ\n");
            format();
            printf("��ӭ�ٴ�ʹ�ã��ݰݣ�\n");
            system("pause");
            exit(0);
            break;
        default:
            printf("�����������������룡\n");
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
