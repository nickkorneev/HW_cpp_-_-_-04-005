#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct unitCell {
    int particles;
    sf::RectangleShape cell;
};

class Grid {
public:
    int width, height;
    float cellSize;

public:
    std::vector<std::vector<unitCell>> Cells;

    Grid(int w, int h, float cell_size, int startNumberinEachCell) {
        width = w;
        height = h;
        cellSize = cell_size;
        for (int i = 0; i < height; i++) {
            std::vector<unitCell> line;
            for (int j = 0; j < width; j++) {
                unitCell cell;
                cell.cell.setSize((sf::Vector2f(cellSize, cellSize)));
                cell.cell.setPosition(sf::Vector2f(cellSize * j, cellSize * i));
                cell.cell.setFillColor(sf::Color(10, 0, 10));
                cell.cell.setOutlineThickness(3);
                cell.cell.setOutlineColor(sf::Color(45, 0, 40));                
                cell.particles = startNumberinEachCell;
                line.push_back(cell);
            }
            Cells.push_back(line);
        }
    }

    void makeStep(const Grid & oldGrid) {
        int y;
        y = 0;
        for (auto line : oldGrid.Cells) {
            int x = 0;
            for (auto cell : line) {
                if (x > 0 and y > 0 and x < width - 1 and y < height - 1) {
                    for (unsigned int i = 0; i < cell.particles; i++) {
                        int way = 1 + std::rand() / ((RAND_MAX + 1u) / 9);
                        if (way == 1) Cells[y - 1][x + 1].particles++;
                        if (way == 2) Cells[y][x].particles++;
                        if (way == 3) Cells[y + 1][x].particles++;
                        if (way == 4) Cells[y - 1][x].particles++;
                        if (way == 5) Cells[y][x + 1].particles++;
                        if (way == 6) Cells[y][x - 1].particles++;
                        if (way == 7) Cells[y + 1][x + 1].particles++;
                        if (way == 8) Cells[y - 1][x - 1].particles++;
                        if (way == 9) Cells[y + 1][x - 1].particles++;
                    }
                }
                x++;   
            }    
            y++;
        }
    }

    void fitColors(){
        for (auto& line : Cells) {
            for (auto& cell : line) {
                cell.cell.setFillColor(sf::Color(0, 0, 255 - 1000/(cell.particles + 5)));
            }
        }
    }  
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Korneev");
    Grid oldGrid(30, 22, 25, 20);  
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Grid newGrid(oldGrid.width, oldGrid.height, oldGrid.cellSize, 0);
        
        newGrid.makeStep(oldGrid);
        
        
        newGrid.fitColors();
        
        window.clear();
        for (auto line : newGrid.Cells) {
            for (auto cell : line) {
                window.draw(cell.cell);
            }
        }
        window.display();
        sf::Int32 time_to_sleep = int(1000.f / 10);
        if (time_to_sleep > 0) {
            //sf::sleep(sf::milliseconds(time_to_sleep));
        }
        oldGrid = newGrid;
    }

    return 0;
}
