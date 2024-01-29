#include "../include/assembler.hpp"

// Cleaner for multithread
void Assemble::cleanerThread(std::vector<TokenLine>& lines, std::vector<LabelLine>& collector, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < lines[i].size(); j++) {
            if (lines[i][j].type == SpecCode::UNKNOWN) { // unknown tokens
                if (isInteger(lines[i][j].name)) {
                    lines[i][j].type = SpecCode::NUMBER; // number
                    continue;
                }
                int adr = labels.getAddress(lines[i][j].name); // check label
                if (adr > -1) {
                    lines[i][j] = { SpecCode::LABEL, lines[i][j].name };
                    collector[i] = { false, j };
                    continue;
                }
                adr = value_names.getAddress(lines[i][j].name); // check value name
                if (adr != -1) {
                    lines[i][j] = { SpecCode::ADDRESS, std::to_string(adr) };
                    continue;
                }
                collector[i] = { true, 0 };
            }
            if (lines[i][0].type == SpecCode::UNKNOWN) {
                collector[i] = { true, 0 };
            }
        }
    }
}

void Assemble::cleaner() {
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][0].type == SpecCode::UNKNOWN) {
            if (lines[i][1].type == SpecCode::DIRECTORY) { // data declaration
                processDirectory(lines[i]);
            }
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
        if (lines[i][0].type == SpecCode::LABEL ) {
            labels.pushLabel(lines[i][0].name, i);
            lines.erase(lines.begin() + i); // cleaning, because if its a label =>
            i--; // remember the address, if its a data declaration => is a preproc instr
            continue;
        }
    }

    const size_t numThreads = std::thread::hardware_concurrency();
    const size_t chunkSize = lines.size() / numThreads;

    std::vector<std::thread> threads;
    std::vector<size_t> threadStarts;

    std::vector<LabelLine> collector(lines.size());

    //
    for (size_t i = 0; i < numThreads; ++i) {
        threadStarts.push_back(i * chunkSize);
        if (i == numThreads - 1) {
            threads.emplace_back(&Assemble::cleanerThread, this, std::ref(lines), std::ref(collector), i * chunkSize, lines.size());
        } else {
            threads.emplace_back(&Assemble::cleanerThread, this, std::ref(lines), std::ref(collector), i * chunkSize, (i + 1) * chunkSize);
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
    //

    size_t deleted = 0;
    for  (size_t i = 0; i < lines.size(); i++) {
        if (collector[i].del) { 
            deleted++;
            lines.erase(lines.begin() + i);
            collector.erase(collector.begin() + i);
            i--;
            continue;
        }
        if (collector[i].j != 0) {
            int adr = labels.getAddress(lines[i][collector[i].j].name);
            lines[i][collector[i].j] = { SpecCode::LABEL, std::to_string(adr - deleted) };
        }
    }
}

// аргументы: тип данных, количество потоков
// сделать метод filter для вектора, который будет принимать 
// функцию T -> bool и из вектора удалить те значения, для 
// которых true, замерить время, доп параметр на метод N - число потоков