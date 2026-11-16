#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// 지출 한 건의 정보를 저장하는 클래스
class Expense {
public:
    string date;         // 날짜 (예: 2026-11-01)
    string category;     // 항목 (예: Food)
    string description;  // 내용 (예: Lunch)
    int amount;          // 금액 (원)

    // 지출 한 건을 한 줄로 출력
    void printInfo() const {
        cout << date << " | " << category << " | "
             << description << " | " << amount << "원" << endl;
    }
};

// 여러 지출 내역을 관리하는 클래스
class ExpenseManager {
private:
    vector<Expense> expenses;  // 모든 지출 내역

public:
    // 새 지출 내역을 vector에 추가
    void addExpense(const Expense& item) {
        expenses.push_back(item);
    }

    // 저장된 모든 지출 내역을 한 줄씩 출력
    void showExpenses() const {
        if (expenses.empty()) {
            cout << "저장된 지출 내역이 없습니다." << endl;
            return;
        }
        for (const Expense& item : expenses) {
            item.printInfo();
        }
    }

    // 모든 금액을 누적하여 총지출 계산
    int calculateTotal() const {
        int total = 0;
        for (const Expense& item : expenses) {
            total += item.amount;
        }
        return total;
    }
};

// 메뉴 출력
void printMenu() {
    cout << "\n========== PERSONAL EXPENSE MANAGER ==========" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. Show All Expenses" << endl;
    cout << "3. Show Total Expense" << endl;
    cout << "4. Exit" << endl;
    cout << "Select: ";
}

// 사용자에게 지출 정보를 입력받아 Expense 객체로 반환
Expense inputExpense() {
    Expense e;
    cout << "Date (예: 2026-11-01): ";
    getline(cin, e.date);
    cout << "Category (예: Food): ";
    getline(cin, e.category);
    cout << "Description (예: Lunch): ";
    getline(cin, e.description);

    // 금액은 정수 입력만 허용 (잘못 입력하면 다시 입력)
    while (true) {
        cout << "Amount (원): ";
        if (cin >> e.amount && e.amount > 0) break;
        cout << "금액은 0보다 큰 정수로 입력하세요." << endl;
        cin.clear();                                          // 오류 상태 해제
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 잘못된 입력 버리기
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');      // 개행 문자 제거
    return e;
}

int main() {
    ExpenseManager manager;
    int choice = 0;

    while (true) {
        printMenu();
        if (!(cin >> choice)) {                               // 숫자가 아닌 입력 처리
            if (cin.eof()) break;                             // 입력 끝이면 종료
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다. 1~4 사이의 숫자를 입력하세요." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // getline() 전에 버퍼 비우기

        if (choice == 1) {
            manager.addExpense(inputExpense());
            cout << "지출이 등록되었습니다." << endl;
        } else if (choice == 2) {
            manager.showExpenses();
        } else if (choice == 3) {
            cout << "Total Expense: " << manager.calculateTotal() << "원" << endl;
        } else if (choice == 4) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다. 1~4 사이의 숫자를 입력하세요." << endl;
        }
    }
    return 0;
}