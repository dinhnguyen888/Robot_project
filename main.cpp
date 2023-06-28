#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
/// <summary>
/// thầy ơi do tụi em sài thư viện từ bên ngoài nên nếu thầy muốn chạy file của tụi em thì thầy phải config một số thứ ạ 
/// thầy mở file Bot_project.sln để mở bài tập lớn ạ
/// Em gửi link config thư viện:https://gamedevspot.net/index.php/forum/do-hoa/38-sfml-tutorial-ca-i-a-t-sfml-ep1-pha-n-1
/// </summary>

using namespace std;

struct Element {
    int value;
    int has_check = 0;
    int has_check2 = 0;
    

};
// luu gia tri va toa do cua moi diem robot di qua
struct {
    std::vector<int> Value;
    std::vector<std::pair<int, int>> path;
} R1, R2;


//ham tim duong di robot
int findMaxNearElement(Element** a, int x1, int y1, int ROW, int COL, int step, ofstream& outputFile) {
    if (x1 < 0 || y1 < 0 || x1 >= ROW || y1 >= COL || a[x1][y1].has_check == 1) return step;
    R1.path.push_back(std::make_pair(x1, y1));
    a[x1][y1].has_check = 1;
    step++;
    R1.Value.push_back(a[x1][y1].value);

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };
    int maxVal = 0, maxIdx = 0;

    // kiem tra 4 o lan can tim o lon nhat
    for (int i = 0; i < 4; i++) {
        int nx = x1 + dx[i], ny = y1 + dy[i];
        if (nx >= 0 && ny >= 0 && nx < ROW && ny < COL && a[nx][ny].has_check == 0) {
            if (a[nx][ny].value > maxVal) {
                maxVal = a[nx][ny].value;
                maxIdx = i;
            }
        }
    }


    return findMaxNearElement(a, x1 + dx[maxIdx], y1 + dy[maxIdx], ROW, COL, step, outputFile);


}

int findMaxNearElement2(Element** a, int x2, int y2, int ROW, int COL, int step, ofstream& outputFile) {
    if (x2 < 0 || y2 < 0 || x2 >= ROW || y2 >= COL || a[x2][y2].has_check2 == 1) return  step;
    
    R2.path.push_back(std::make_pair(x2, y2));

    a[x2][y2].has_check2 = 1;
    step++;
    R2.Value.push_back(a[x2][y2].value);

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };
    int maxVal = 0, maxIdx = 0;

    // kiem tra 4 o lan can, tim o lon nhat
    for (int i = 0; i < 4; i++) {
        int nx = x2 + dx[i], ny = y2 + dy[i];
        if (nx >= 0 && ny >= 0 && nx < ROW && ny < COL && a[nx][ny].has_check2 == 0) {
            if (a[nx][ny].value > maxVal) {
                maxVal = a[nx][ny].value;
                maxIdx = i;
            }
        }
    }


    return findMaxNearElement2(a, x2 + dx[maxIdx], y2 + dy[maxIdx], ROW, COL, step, outputFile);

}
int findRoad2Robot(Element** a, int x1, int y1, int x2, int y2, int ROW, int COL, ofstream& outputFile) {
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };
    if (x1 < 0 || y1 < 0 || x1 >= ROW || y1 >= COL || a[x1][y1].has_check == 1)
        if (x2 < 0 || y2 < 0 || x2 >= ROW || y2 >= COL || a[x2][y2].has_check == 1) //2 robot het duong di 
            return 0;
        else // robot 2 con duong di
        {
            a[x2][y2].has_check = 1;
            outputFile << "robot 2: " << a[x2][y2].value << "; " << endl;

            int maxVal_2 = 0, maxIdx_2 = 0;

            for (int i = 0; i < 4; i++) {
                int nx2 = x2 + dx[i], ny2 = y2 + dy[i];
                if (nx2 >= 0 && ny2 >= 0 && nx2 < ROW && ny2 < COL && a[nx2][ny2].has_check == 0) {
                    if (a[nx2][ny2].value > maxVal_2) {
                        maxVal_2 = a[nx2][ny2].value;
                        maxIdx_2 = i;

                    }
                }
            }
            return findRoad2Robot(a, x1, y1, x2 + dx[maxIdx_2], y2 + dy[maxIdx_2], ROW, COL, outputFile);

        }
    else
    {
        if (x2 < 0 || y2 < 0 || x2 >= ROW || y2 >= COL || a[x2][y2].has_check == 1) // robot 1 con duong di
        {
            a[x1][y1].has_check = 1;
            outputFile << "robot 1: " << a[x1][y1].value << "; " << endl;

            int maxVal = 0, MaxIdx = 0;

            for (int i = 0; i < 4; i++) {
                int nx1 = x1 + dx[i], ny1 = y1 + dy[i];
                if (nx1 >= 0 && ny1 >= 0 && nx1 < ROW && ny1 < COL && a[nx1][ny1].has_check == 0) {
                    if (a[nx1][ny1].value > maxVal) {
                        maxVal = a[nx1][ny1].value;
                        MaxIdx = i;
                    }
                }
            }
            return	findRoad2Robot(a, x1 + dx[MaxIdx], y1 + dy[MaxIdx], x2, y2, ROW, COL, outputFile);
        }

        else // ca 2 robot con duong di 
        {
            a[x1][y1].has_check = 1;
            a[x2][y2].has_check = 1;

            outputFile << "robot 1: " << a[x1][y1].value << "; ";
            outputFile << "robot 2: " << a[x2][y2].value << "; " << endl;


            int maxVal = 0, maxIdx = 0;
            int maxVal_2 = 0;
            int maxIdx_2 = 0;
            int nx1, ny1;
            for (int i = 0; i < 4; i++) {
                nx1 = x1 + dx[i], ny1 = y1 + dy[i];
                if (nx1 >= 0 && ny1 >= 0 && nx1 < ROW && ny1 < COL && a[nx1][ny1].has_check == 0) {
                    if (a[nx1][ny1].value > maxVal) {
                        maxVal = a[nx1][ny1].value;
                        maxIdx = i;
                    }
                }
            }
            nx1 = x1 + dx[maxIdx], ny1 = y1 + dy[maxIdx];
            int nx2, ny2;
            for (int j = 0; j < 4; j++) {
                nx2 = x2 + dx[j], ny2 = y2 + dy[j];
                if (nx1 == nx2 && ny1 == ny2)
                    continue;
                else
                    if (nx2 >= 0 && ny2 >= 0 && nx2 < ROW && ny2 < COL && a[nx2][ny2].has_check == 0) {
                        if (a[nx2][ny2].value > maxVal_2) {
                            maxVal_2 = a[nx2][ny2].value;
                            maxIdx_2 = j;
                        }
                    }
            }


            return findRoad2Robot(a, x1 + dx[maxIdx], y1 + dy[maxIdx], x2 + dx[maxIdx_2], y2 + dy[maxIdx_2], ROW, COL, outputFile);
        }
    }

}


void createGraphics(Element** a, int option, const int COL, const int ROW, int x1, int y1, int x2, int y2) {


    const int windowWidth = 300;
    const int windowHeight = 350;
    const int rectSize = std::min(windowWidth / COL, windowHeight / ROW);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "matrix");

    // tao ra o trong ma tran 
    sf::RectangleShape cells[6][5];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cells[i][j].setSize(sf::Vector2f(rectSize, rectSize));
            cells[i][j].setPosition(j * rectSize, i * rectSize);
            cells[i][j].setFillColor(sf::Color::White);
            cells[i][j].setOutlineThickness(1);
            cells[i][j].setOutlineColor(sf::Color::Black);
        }
    }

    // tao font chu va co chu
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font" << std::endl;

    }
    const int maxStringLength = 10; // do dai toi da trong 1 o 
    sf::Text values[6][5];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            std::string cellValue = std::to_string(a[i][j].value);

            if (cellValue.length() > maxStringLength) {
                cellValue = cellValue.substr(0, maxStringLength - 3) + "...";
            }
            values[i][j].setFont(font);
            values[i][j].setString(cellValue);
            values[i][j].setCharacterSize(rectSize / 3);
            values[i][j].setFillColor(sf::Color::Black);
            values[i][j].setPosition(j * rectSize + rectSize / 4, i * rectSize + rectSize / 4);

        }
    }



    // vong lap duy tri cua so
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // ve o va chu trong ma tran
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                window.draw(cells[i][j]);
                window.draw(values[i][j]);
            }
        }
        if (option == 1) {
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    if (a[i][j].has_check == 1) {
                        cells[i][j].setFillColor(sf::Color(200, 200, 200));
                    }
                    else {
                        cells[i][j].setFillColor(sf::Color::White);
                    }
                }
            }
            // ve duong thang ket noi cac diem lai voi nhau
            for (int i = 1; i < R1.path.size(); i++) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(R1.path[i - 1].second * rectSize + rectSize / 2, R1.path[i - 1].first * rectSize + rectSize / 2), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(R1.path[i].second * rectSize + rectSize / 2, R1.path[i].first * rectSize + rectSize / 2), sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }
            window.display();
        }
        if (option == 2 ) {
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    cells[x1][y1].setFillColor(sf::Color::Red);
                    cells[x2][y2].setFillColor(sf::Color::Blue);
                  
                    if (a[i][j].has_check == 1 && a[i][j].has_check2 == 1) {
                        cells[i][j].setFillColor(sf::Color::Cyan);
                    }
                    else {
                        cells[i][j].setFillColor(sf::Color::White);
                    }
                }
            }

            for (int i = 1; i < R1.path.size(); i++) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(R1.path[i - 1].second * rectSize + rectSize / 2, R1.path[i - 1].first * rectSize + rectSize / 2), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(R1.path[i].second * rectSize + rectSize / 2, R1.path[i].first * rectSize + rectSize / 2), sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }
            for (int i = 1; i < R2.path.size(); i++) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(R2.path[i - 1].second * rectSize + rectSize / 3, R2.path[i - 1].first * rectSize + rectSize / 3), sf::Color::Blue),
                    sf::Vertex(sf::Vector2f(R2.path[i].second * rectSize + rectSize / 3, R2.path[i].first * rectSize + rectSize / 3), sf::Color::Blue)
                };
                window.draw(line, 2, sf::Lines);
            }
            window.display();
        }

    }
}


int main() {

    // doc du lieu nhap tu file input
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        int ROW;
        int COL;
        inputFile >> ROW;
        inputFile >> COL;
        Element** arr = new Element * [ROW];
        for (int i = 0; i < ROW; i++) {
            arr[i] = new Element[COL];
        }
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                inputFile >> arr[i][j].value;
            }
        }
        inputFile.close();

        int option;
        cout << "chon che do:" << endl << "1.chon 1 robot va xuat ket qua duong di" << endl << "2.chon 2 robot va xuat ket qua duong di 2 robot va vi tri robot trung nhau" << endl << "3.chon 2 robot va xuat ket qua 2 robot di duong khac nhau " << endl;
        cin >> option;

        //xuat du lieu ra file output.txt
        ofstream outputFile("output.txt");
        if (outputFile.is_open()) {

            outputFile << endl;
            if (option == 1) {
                int x1, y1;
                cout << "nhap toa do robot 1:";
                cin >> x1 >> y1;

                outputFile << findMaxNearElement(arr, x1, y1, ROW, COL, 0, outputFile) << endl;
                for (int i = 0; i < R1.Value.size(); i++) {
                    outputFile << R1.Value[i] << " ";
                }
               createGraphics(arr, option, COL, ROW, x1, y1, x1, y1);
                outputFile.close();
            }
            if (option == 2)
            {
                int x1, x2, y1, y2;
                cout << "nhap toa do robot 1:";
                cin >> y1 >> x1;
                cout << "nhap toa do robot 2:";
                cin >> y2 >> x2;
                if (x1 == x2 && y1 == y2) {  //them vong lap ngan toa do trung nhau
                    cout << "toa do 2 robot trung nhau khong hop le yeu cau bai toan " << endl;
                }
                else {

                    outputFile << "robot 1 di duoc" << findMaxNearElement(arr, x1, y1, ROW, COL, 0, outputFile) << endl;
                    for (int i = 0; i < R1.Value.size(); i++) {
                        outputFile << R1.Value[i] << " ";
                    }

                    outputFile << endl << "robot 2 di duoc:" << findMaxNearElement2(arr, x2, y2, ROW, COL, 0, outputFile) << endl;
                    for (int i = 0; i < R1.Value.size(); i++) {
                        outputFile << R2.Value[i] << " ";
                    }
                    createGraphics(arr, option, COL, ROW, x1, y1, x2, y2);
                    // dem so o di qua boi 2 robot

                    int count = 0;
                    outputFile << endl << "o robot di trung nhau:";
                    for (int i = 0; i < ROW; i++) {
                        for (int j = 0; j < COL; j++) {
                            if (arr[i][j].has_check == 1 && arr[i][j].has_check2 == 1) {
                                count++;
                                outputFile << arr[i][j].value << " ";
                            }
                        }
                    }
                    outputFile << endl << "So o ma ca 2 robot di qua: " << count << endl;


                    outputFile.close();
                }
            }

            if (option == 3) {
                int x1, x2, y1, y2;
                cout << "nhap toa do robot 1:(x,y)";
                cin >> x1 >> y1;
                cout << "nhap toa do robot 2:(x,y)";
                cin >> x2 >> y2;

                findRoad2Robot(arr, x1, y1, x2, y2, ROW, COL, outputFile);
                
                outputFile.close();
            }
            
            // xoa bo nho dong
            for (int i = 0; i < ROW; i++) {
                delete[] arr[i];
            }
            delete[] arr;
            return 0;
        }
        else {
            cout << "Unable to open input file" << endl;
            return 1;
        }
        return 0;
    }
}

