struct Dice
{
	Dice(const char* str)
	{
		for (int i = 0; i < 6 && *str != '\0'; i++, str++)
			side[i] = *str;
	}

	char side[6];
};

class WordDice
{
	typedef unordered_set<int> _dice_idx;
	_dice_idx char_dices[26];
	int n_dice;
public:
	WordDice()
	{
		n_dice = 0;
	}

	bool setDices(const vector<Dice>& dices)
	{
		for (int idxDice = 0, n = dices.size(); idxDice < n; idxDice++)
		{
			const Dice& dice = dices[idxDice];
			for (int i = 0; i < 6; i++)
			{
				char ch = dice.side[i];
				if (!isalpha(ch))
					return false;

				char_dices[tolower(ch) - 'a'].insert(idxDice);
			}
		}
		n_dice = dices.size();
		return true;
	}

	bool canMakeWord(const string& word)
	{
		if (word.size() > n_dice)
			return false;

		vector<int> char_idxes(word.size());
		for (int i = 0, n = word.size(); i < n;i++)
		{
			char ch = word[i];
			if (!isalpha(ch))
				return false;

			char_idxes[i] = tolower(ch) - 'a';
		}
		unordered_set<int> used;

		vector<int> sel_dices(word.size());
		if (canMakeWord(char_idxes, 0, used, sel_dices))
		{
			for(int dice:sel_dices)
				cout<<dice<<", ";
			cout << endl;
		}
		else
			return false;
	}

protected:
	bool canMakeWord(const vector<int>& char_idxes, int index, unordered_set<int>& used, vector<int>& sel_dices)
	{
		if (index == char_idxes.size())
			return true;

		int ch_idx = char_idxes[index];
		for (int dice : char_dices[ch_idx])
		{
			if (used.find(dice) == used.end())
			{
				used.insert(dice);

				sel_dices[index] = dice;
				if (canMakeWord(char_idxes, index + 1, used, sel_dices))
					return true;

				used.erase(dice);
			}
		}
		return false;
	}

};

int main()
{
	WordDice wordDice;
	wordDice.setDices({ {"iqepjw", "lrvqik", "jtejru", "unamsd", "wpqnfy"} });
	if(!wordDice.canMakeWord("tape"))
		cout<<"not matched";
	return 0;
}
