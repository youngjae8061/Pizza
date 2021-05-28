#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>	    // bool, true, false�� ���ǵ� ��� ����
#include<Windows.h>		// ������ �ܼ�â ���� ��� ���� 

   /////////////////////////////////////////////////
  //              ����������Ʈ 8��                //
 // ���� - ��â��   ���� - ������, ����, �̿��� //
////////////////////////////////////////////////

// �ֹ� ���
typedef struct order {
	char menu[20];		// �޴� �̸�
	int count;			// �ش� �޴� ����
	int price;			// ����
	int pizza;			// 0�̸� �Ϲ�, 1�̸� �����̾�, 3�̸� ���̵� �� ����
	struct order* next;	//
}order;
order* order_h;			// �ֹ������ �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 

// ����� ���� ���
typedef struct user_info{
	char name[20];		// ����� �̸�
	int phone;			// ����� ��ȭ��ȣ
	int visit;			// ����� �湮 Ƚ��
	struct order* next;	//
}info;
info* info_h;		    // ����� ���� ����� �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 

// �� ���� ���
typedef struct user_manage {
	char name[20];				// ����� �̸�
	int phone;					// ����� ��ȭ��ȣ
	int visit;					// ����� �湮 Ƚ��
	struct user_manage* next;	//
}mng;
mng* mng_h;					    // �� ���� ����� �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 

// ���̺� ���� ���
typedef struct table {
	// bool table;				// True �ڸ� ����, False �ڸ� ����
    int table1;
    struct user_info* next1;
    int table2;
    struct user_info* next2;
    int table3;
    struct user_info* next3;
    int table4;
    struct user_info* next4;

}tb;
tb* tb_h;				    // �ֹ������ �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 


void program_info();            // ���α׷� ���� ���
void user_menu();               // ����� �޴� ���
void menu_info();               // ���� �޴� ���
void input_menu();              // �޴� �Է�(�����)
void middle_bill();		        // �߰� ��� ������
void last_bill();		        // ���� ������


int main() {
	SetConsoleTitle(TEXT("Pizza Store - ����������Ʈ 13�й� 8��")); // �ܼ�â ����

    int num = 0;
    order* head = NULL;
    head = (order*)malloc(sizeof(order));
    head->next = NULL;

    program_info();

    while (1)
    {
        user_menu();

        // �޴� �Է½� ���ڰ� �ƴ� ���� �Է½� ���ۿ� �Էµ� ���� �ʱ�ȭ
        if (scanf_s("%d", &num) == 0) {
            system("cls");
            printf("���ڸ� �Է��ϼ̳׿�. �޴��� ��.��.��. �����ּ���.\n\n");
            rewind(stdin);
        }
        else { // ���������� �޴��� �Է����� �� switch�� ����
            switch (num) {
                case 1: // �ֹ�
                    printf("�ֹ��ϱ⸦ �����ϼ̽��ϴ�. \n");
                    menu_info();
                    input_menu();
                    break;
                case 2: // �ֹ� ����
                    printf("~ \n");
                    break;
                case 3: // �߰� ��꼭 ���
                    printf("~ \n");
                    break;
                case 4: // ���
                    printf("~ \n");
                    break;
                case 5: return 0; // ����
                default:
                    system("cls");
                    printf(" �޴��� �ִ� 1 ~ 5 ������ ��.��.��. ��������!!!!! \n\n");
                    break;
            }
        }
    }

	return 0;
}


void program_info()
{
    printf("------------------------------------------------\n");
    printf("               ���� ����  ���α׷�              \n");
    printf("   8�� : ��â��(����), ����, ������, �̿���   \n");
    printf("------------------------------------------------\n\n\n");
}


void menu_info()
{
    printf("          [�޴���]           \n");
    printf("        �����̾� ����        \n");
    printf("-----------------------------\n");
    printf("������ ����          26,000  \n");
    printf("�ع� ����            28,000  \n");
    printf("�ֽ����̽� ����      24,000  \n");
    printf("�����޺���̼� ����  26,000  \n");
    printf("-----------------------------\n");
    printf("          �Ϲ� ����          \n");
    printf("-----------------------------\n");
    printf("�Ұ�� ����          20,000  \n");
    printf("���� ����          19,000  \n");
    printf("�������� ����        19,000  \n");
    printf("����δ� ����        19,000  \n");
    printf("-----------------------------\n");
    printf("           ���̵�            \n");
    printf("-----------------------------\n");
    printf("��&��(6����)          6,000  \n");
    printf("ġŲ�ٴ�(6����)       6,000  \n");
    printf("���İ�Ƽ              7,000  \n");
    printf("ġ�                5,000  \n");
    printf("-----------------------------\n");
    printf("            ����             \n");
    printf("-----------------------------\n");
    printf("�ݶ�                  2,000  \n");
    printf("���̴�                2,000  \n");
    printf("-----------------------------\n");

}


void input_menu()
{
    order* curr = NULL;
    order* end = NULL;
    curr = (order*)malloc(sizeof(order));
    curr->next = NULL;

    printf("?\n");
}


void middle_bill() {
    int table_num;              // ���̺� ��ȣ
    int sum = 0;                // �Ѱ���
    int event_pizza_p = 0;      // �����̾� ���� ���αݾ�
    int pizza_p_count = 0;      // �����̾� ���� ����, �̺�Ʈ ���� 
    int event_pizza_c = 0;      // �Ϲ� ���� ���αݾ�
    int pizza_c_count = 0;      // �Ϲ� ���� ����, �̺�Ʈ ����
    int first_order = 0;        // ù �ֹ� ���� �ݾ�
    int five_order = 0;         // 5�� �ֹ� ���� �ݾ�
    int event = 0;              // �� ���αݾ�

    info* tmp = info_h;         // user ����� ���� ����
    mng* who = mng_h;           // ����� user ����
    order* list = order_h;      // order �ֹ��޴� �о���� ����

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num);

    switch (table_num) {
        case 1:
            if (tb_h->table1 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next1;  // ����� ���� tmp
            list = tmp->next;   // �ֹ� �޴� 
            order_h = list;  // �ֹ� �޴�(head)
            break;
        case 2:
            if (tb_h->table2 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next2;
            list = tmp->next;
            order_h = list;
            break;
        case 3:
            if (tb_h->table3 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next3;
            list = tmp->next;
            order_h = list;
            break;
        case 4:
            if (tb_h->table4 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next4;
            list = tmp->next;
            order_h = list;
            break;
    }

    // �ֹ�����(������)
    printf("\t\t�߰� ������ ���\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d��\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;       // �Ϲ����� ����
        else if (list->pizza == 1) pizza_p_count++;   // �����̾� ���� ����
        list = list->next;
    }

    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // ù�ֹ� �̺�Ʈ
            if (who->visit == 1) {
                first_order = 3000;
                printf("ù �湮 ���� �̺�Ʈ\t\t%d\n", first_order);
            }
            // 5�� �湮 �̺�Ʈ
            if (who->visit == 5) {
                five_order = 5000;
                printf("5�� �湮 ���� �̺�Ʈ\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t%d\n", sum);
    return 1;
}


void last_bill() {
    int pay;
    int table_num;              // ���̺� ��ȣ
    int sum = 0;                // �Ѱ���
    int event_pizza_p = 0;      // �����̾� ���� ���αݾ�
    int pizza_p_count = 0;      // �����̾� ���� ����, �̺�Ʈ ���� 
    int event_pizza_c = 0;      // �Ϲ� ���� ���αݾ�
    int pizza_c_count = 0;      // �Ϲ� ���� ����, �̺�Ʈ ����
    int first_order = 0;        // ù �ֹ� ���� �ݾ�
    int five_order = 0;         // 5�� �ֹ� ���� �ݾ�
    int event = 0;              // �� ���αݾ�

    info* tmp = info_h;         // user ����� ���� ����
    mng* who = mng_h;           // ����� user ����
    order* list = order_h;      // order �ֹ��޴� �о���� ����
    order* pre;                 // free(�ֹ��޴�)

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num);
    switch (table_num) {
    case 1:
        if (tb_h->table1 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next1;  // ����� ���� tmp
        list = tmp->next;   // �ֹ� �޴� 
        order_h = list;  // �ֹ� �޴�(head)
        break;
    case 2:
        if (tb_h->table2 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next2;
        list = tmp->next;
        order_h = list;
        break;
    case 3:
        if (tb_h->table3 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next3;
        list = tmp->next;
        order_h = list;
        break;
    case 4:
        if (tb_h->table4 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next4;
        list = tmp->next;
        order_h = list;
        break;
    }

    // �ֹ�����(������)
    printf("\t\t�߰� ������ ���\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d��\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;     // �Ϲ����� ����
        else if (list->pizza == 1) pizza_p_count++; // �����̾� ���� ����
        list = list->next;
    }
    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // ù�ֹ� �̺�Ʈ
            if (who->visit == 1) {
                first_order = 3000;
                printf("ù �湮 ���� �̺�Ʈ\t\t%d\n", first_order);
            }
            // 5�� �湮 �̺�Ʈ
            if (who->visit == 5) {
                five_order = 5000;
                printf("5�� �湮 ���� �̺�Ʈ\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t%d\n", sum);
    return sum;

    printf("�ѱݾ���  %d�� �Դϴ�.\n", sum);
    printf("���� �ݾ��� �Է����ּ��� : ");
    scanf_s("%d", &pay);
    if (sum == pay) {
        printf("������ �Ϸ�Ǿ����ϴ�.\n");
        // ���̺� ���� ����
        list = tmp->next;
        switch (table_num) {
            case 1:
                tb_h->next1 = NULL; // ���̺� ���� ����
                tb_h->table1 = 0;   // ���̺� �ڸ� ����
                free(tmp);          // ���� free
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 2:
                tb_h->next2 = NULL;
                tb_h->table2 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 3:
                tb_h->next3 = NULL;
                tb_h->table3 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 4:
                tb_h->next4 = NULL;
                tb_h->table4 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
        }
        return 1;
    }
    else if (sum > pay) {
        printf("�����ݾ��� �����մϴ�. �ٽ� �������ּ���\n");
        return 0;
    }
    else {
        printf("�ѱݾ��� �ʰ��Ͽ����ϴ�. �ٽ� �������ּ���\n");
        return 0;
    }
}


void user_menu() {
    printf("===========================\n");
    printf("�ݰ����ϴ� �մ�.\n�޴��� �������ּ��� :)\n");
    printf("===========================\n");
    printf("1. �ֹ�\n");
    printf("2. �ֹ� ����\n");
    printf("3. �߰� ��꼭 ���\n");
    printf("4. ���\n");
    printf("5. ����\n");
    printf("===========================\n\n");
    printf("�޴��� �Է��ϼ��� : ");
}