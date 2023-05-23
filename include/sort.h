#ifndef SORT_H
#define SORT_H

#include "config.h"
#include "perf.h"
#include <vector>
using namespace Perf;

namespace Sort 
{

    template<typename T, class Compare >
    void InsertionSort(std::vector<T> &v, Compare cmp, Performance& perf)
    {   
#ifdef ENABLE_PERF
        perf.get_timer().start();
#endif
        int i, j;
        T key;
        for (i = 1; i < v.size(); i++) {
            key = v[i];
            j = i - 1;
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
            while (j >= 0 && cmp(key, v[j])) {
                v[j + 1] = v[j];
                j--;
#ifdef ENABLE_PERF
                perf.get_counter().increment_comparisons();
                perf.get_counter().increment_swaps();
#endif
            }
            v[j + 1] = key;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
        perf.get_timer().stop();
    }

    // Implementação do algoritmos de ordenação basicos O(n^2)
    // Escolha uns dos métodos abaixo para implementar
    //  - BubbleSort
    //  - SelectionSort
    //  - InsertionSort
    template<typename T, class Compare >
    void BasicSort(std::vector<T> &v, Compare cmp)
    {
        Perf::Performance perf;
        InsertionSort(v, cmp, perf);
#ifdef ENABLE_PERF
        std::cout << "BasicSort (InsertionSort): " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;    
#endif 
    }

    template<typename T, class Compare >
    void Merge(std::vector<T> &v, int low, int mid, int hight, Compare cmp, Performance &perf)
    {
        int i, j, k;
        int n1 = mid - low + 1;
        int n2 = hight - mid;

        std::vector<T> L(n1), R(n2);

        for (i = 0; i < n1; i++) {
            L[i] = v[low + i];
        }
        for (j = 0; j < n2; j++) {
            R[j] = v[mid + 1 + j];
        }

        i = 0;
        j = 0;
        k = low;

        while (i < n1 && j < n2) {
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
            if (cmp(L[i], R[j])) {
                v[k] = L[i];
                i++;
            } else {
                v[k] = R[j];
                j++;
            }
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();   
#endif  
            k++;
        }

        while (i < n1) {
            v[k] = L[i];
            i++;
            k++;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();   
#endif  
        }

        while (j < n2) {
            v[k] = R[j];
            j++;
            k++;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
    }

    template<typename T, class Compare >
    void MergeSort(std::vector<T> &v, int low, int hight, Compare cmp, Performance &perf)
    {
        if (low < hight) {
            int mid = (low + hight) / 2;
            MergeSort(v, low, mid, cmp, perf);
            MergeSort(v, mid + 1, hight, cmp, perf);
            Merge(v, low, mid, hight, cmp, perf);
        }
    }


    // Implementação algoritmo de ordenação MergeSort
    template<typename T, class Compare >
    void MergeSort(std::vector<T> &v, Compare cmp)
    {
        Perf::Performance perf;
        MergeSort(v, 0, v.size() - 1, cmp, perf);
#ifdef ENABLE_PERF
        std::cout << "MergeSort: " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif

    }

    // FIXME: Implementação algoritmo de ordenação QuickSort
    template <typename T, class Compare>
    int partition(std::vector<T> &arr, int low, int high, Compare cmp, Perf::Performance &performanc)
    {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            performanc.get_counter().increment_comparisons();
            if (cmp(arr[j], pivot))
            {
                i++;
                std::swap(arr[i], arr[j]);
                performanc.get_counter().increment_swaps();
            }
        }
        std::swap(arr[i + 1], arr[high]);
        performanc.get_counter().increment_swaps();
        return i + 1;
    }

    template <typename T, class Compare>
    void auxQuickSort(std::vector<T> &arr, int low, int high, Compare cmp, Perf::Performance &performanc)
    {
        if (low < high)
        {
            int pivotIndex = partition(arr, low, high, cmp, performanc);
            auxQuickSort(arr, low, pivotIndex - 1, cmp, performanc);
            auxQuickSort(arr, pivotIndex + 1, high, cmp, performanc);
        }
    }

    template <typename T, class Compare>
    void QuickSort(std::vector<T> &arr, Compare cmp)
    {
        Perf::Performance performanc;
        int n = arr.size();
        auxQuickSort(arr, 0, n - 1, cmp, performanc);
        cout << "QuickSort: Foram feitas " << performanc.get_counter().get_comparisons() << " comparações." << std::endl;
        cout << "QuickSort: Foram feitas " << performanc.get_counter().get_swaps() << " trocas." << std::endl;
    }

    
    //  FIXME: emente algoritmo de ordenação HeapSort
    template <typename T, class Compare>
    void heapify(std::vector<T> &v, int n, int k, Compare cmp, Perf::Performance &performanc)
    {
        int aux = k;           // raiz
        int esq = (2 * k) + 1; // esq = 2*i + 1
        int dir = (2 * k) + 2; // dir = 2*i + 2

        // esq > aux
        performanc.get_counter().increment_comparisons();
        if (esq < n && cmp(v[esq], v[aux]))
            aux = esq;

        // dir > aux
        performanc.get_counter().increment_comparisons();
        if (dir < n && cmp(v[dir], v[aux]))
            aux = dir;

        // se estiver certo
        if (aux != k)
        {
            swap(v[k], v[aux]);
            performanc.get_counter().increment_swaps();
            heapify(v, n, aux, cmp, performanc);
        }
    }

    template <typename T, class Compare>
    void HeapSort(std::vector<T> &v, Compare cmp)
    {
        int n = v.size();

        Perf::Performance performanc;

        // construtor Heap
        for (int k = (n / 2) - 1; k >= 0; k--)
            heapify(v, n, k, cmp, performanc);

        // extrai um por um os elementos da heap
        for (int k = n - 1; k > 0; k--)
        {
            swap(v[0], v[k]);
            performanc.get_counter().increment_comparisons();
            heapify(v, k, 0, cmp, performanc);
        }

        cout << "HeapSort: Foram feitas " << performanc.get_counter().get_comparisons() << " comparações." << std::endl;
        cout << "HeapSort: Foram feitas " << performanc.get_counter().get_swaps() << " trocas." << std::endl;
    }

    // FIXME: Pesquise por algoritmos de ordenação eficientes não vistos em sala de aula.
    //       Implemente um deles.
    template <typename T, class Compare>
    void shellSort(std::vector<T> &v, Compare cmp, int n)
    {
        int i, j, k;
        T temp;
        Perf::Performance performanc;

        for (i = n / 2; i > 0; i = i / 2)
        {
            for (j = i; j < n; j++)
            {
                for (k = j - i; k >= 0; k = k - i)
                {
                    performanc.get_counter().increment_comparisons();
                    if (cmp(v[k], v[k + 1]))
                        break;

                    else
                    {
                        temp = v[k];
                        v[k] = v[k + i];
                        performanc.get_counter().increment_swaps();
                        v[k + i] = temp;
                    }
                }
            }
        }
        cout << "MySort(ShellSort): Foram feitas " << performanc.get_counter().get_comparisons() << " comparações." << std::endl;
        cout << "MySort(ShellSort): Foram feitas " << performanc.get_counter().get_swaps() << " trocas." << std::endl;
    }

    template <typename T, class Compare>
    void MySort(std::vector<T> &v, Compare cmp)
    {
        int n = v.size();
        shellSort(v, cmp, n);
    }

    //Observaçã0:
     // Compare cmp é uma função que recebe dois elementos do tipo T e retorna um bool.
     // Exemplo de como declarar uma função do tipo Compare:
     /*
       struct {
         bool operator() (T &a, T &b) const
            {
                return a < b;
            }
        } cmp;
    */
     // Se cmp(a, b) retorna true, então a é menor que b. 
     // veja nos arquivos de teste como usar essa função.

     // Funçoes auxiliares deve ser implementadas neste arquivo.
}

#endif /* SORT_H */
