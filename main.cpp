#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(960, 600), "Sorter");
int n = 80;
float recHs[80];
bool sorted = false;

void dispSort(int index) {
    window.clear();
    for (int i = 0; i < n; i++) {
        sf::RectangleShape block(sf::Vector2f(10, recHs[i]));
        block.setPosition(i * 12, 600 - recHs[i]);
        block.setFillColor(sorted || i == index ? sf::Color::Green : sf::Color::White);
        window.draw(block);
    }
    window.display();
}

void insertionSort()
{
    Sleep(15);
    int i, key, j;
    for (i = 0; i < n; i++)
    {
        key = recHs[i];
        j = i - 1;

        while (j >= 0 && recHs[j] > key)
        {
            recHs[j + 1] = recHs[j];
            j = j - 1;
            dispSort(j);
        }
        recHs[j + 1] = key;
    }

    sorted = true;

    dispSort(i);
}

void selectionSort()
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (recHs[j] < recHs[min_idx])
                min_idx = j;
        std::swap(recHs[min_idx], recHs[i]);
        dispSort(i);
        Sleep(15);
    }
    sorted = true;
    dispSort(i);
}

void bubbleSort()
{
    Sleep(15);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (recHs[j] > recHs[j + 1])
            {
                std::swap(recHs[j], recHs[j + 1]);
                dispSort(j);
            }
        }
    }
    sorted = true;
    dispSort(n - 1);
}

int partition(float arr[], int low, int high)
{
    float pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
            dispSort(j);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    dispSort(high);
    return (i + 1);
}

void quickSortHelper(float arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort()
{
    Sleep(15);
    quickSortHelper(recHs, 0, n - 1);
    sorted = true;
    dispSort(n - 1);
}

void heapify(float arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        dispSort(i);
        heapify(arr, n, largest);
    }
}

void heapSort()
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(recHs, n, i);

    for (int i = n - 1; i > 0; i--)
    {   
        Sleep(15);
        std::swap(recHs[0], recHs[i]);
        dispSort(i);
        heapify(recHs, i, 0);
    }
    sorted = true;
    dispSort(0);
}

int main() {

    Sleep(5000);

    for (int i = 0; i < 80; i++) {
        recHs[i] = (i + 1) * 7;
    }
    for (int i = 0; i < 80; i++) {
        int start = 1;
        int endd = 80;
        int g = rand() % (endd - start + 1);
        int s = recHs[i];
        recHs[i] = recHs[g];
        recHs[g] = s;
    }
    while (window.isOpen()) {
        sf::Event event;


        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();
            }
        }
        if (!sorted) {
            dispSort(0);
            // Для работы данного кода необходимо раскомментить одну из строк ниже. 
            // Пожалуйста, используйте лишь одну сортировку для корректной работы. 
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
                                      // insertionSort();
                                      // bubbleSort();
                                      // heapSort();
                                      // quickSort();
                                      // selectionSort();
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ // 
        }

    }

}
