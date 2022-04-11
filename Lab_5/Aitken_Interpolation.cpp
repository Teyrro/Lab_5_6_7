#include "Interpolation.h"

void Aitken_Interpolation::FindAnswer() {

	short counter(storageOfData.size());
	std::vector<double> answer(storageOfData.size());
	for (int i(0); i < storageOfData.size(); i++) {
		answer[i] = storageOfData[i].second;
	}

	while (1 < counter--) {
		std::cout << "¬нешн€€ итераци€ " << counter << ", ";
		int l(0), r(storageOfData.size() - counter);
		std::cout << "l - " << l << " r - " << r << " ";
		for (l; l < counter; l++, r++) {
			answer[l] = (answer[l] * (value - storageOfData[r].first) - answer[l + 1] * (value - storageOfData[l].first));
			answer[l] /= (storageOfData[l].first - storageOfData[r].first);
			std::cout << "P" << l << r << " " << answer[l] << " ";
		}
		std::cout << "\n";
	}
	std::cout << answer[0];
	_answer = answer[0];

}