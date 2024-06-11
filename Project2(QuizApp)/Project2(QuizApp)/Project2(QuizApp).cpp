// Main Solution
#include <iostream>
#include <Windows.h>

using namespace std;

enum enQuestionsLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};

enum enOperationType{ Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType OpType) { 
	switch (OpType) { 
		case enOperationType::Add: 
			return"+"; 
		case enOperationType::Sub: 
			return"-"; 
		case enOperationType::Mult:
			return"x"; 
		case enOperationType::Div:
			return"/"; 
		default: 
			return"Mix"; 
	} 
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel) { 
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" }; 
	return arrQuestionLevelText[QuestionLevel - 1]; 
} 

int RandomNumber(int From, int To) { 
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum; 
}

void SetScreenColor(bool Right) {
	if (Right)
		system("color 2F");
	else {
		system("color 4F");
		cout << "\a";
	}
}

short ReadHowManyQuestions() {
	short NumberOfQuestions;
	do {
		cout << "How Many Questions Do You Want To Answer? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel() {
	short QuestionLevel = 0;
	do {
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType() {
	short OpType;
	do {
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";           
		cin >> OpType;
	} while (OpType < 1 || OpType >5); 

	return (enOperationType)OpType;
}

struct stQuestion{ 
	int Number1 = 0; 
	int Number2 = 0; 
	enOperationType OperationType; 
	enQuestionsLevel QuestionLevel; 
	int CorrectAnswer = 0; 
	int PlayerAnswer = 0; 
	bool AnswerResult = false; 
}; 

struct stQuizz{ 
	stQuestion QuestionList[100]; 
	short NumberOfQuestions; 
	enQuestionsLevel QuestionsLevel; 
	enOperationType OpType; 
	short NumberOfWrongAnswers = 0; 
	short NumberOfRightAnswers = 0; 
	bool isPass = false; 
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:
		return Number1 + Number2;
		break;
	case enOperationType::Sub:
		return Number1 - Number2;
		break;
	case enOperationType::Mult:
		return Number1 * Number2;
		break;
	case enOperationType::Div:
		return Number1 / Number2;
		break;
	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType() {
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType) {
	stQuestion Question;
	if (QuestionLevel == enQuestionsLevel::Mix) {
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp) {
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel) {
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);

		Question.QuestionLevel = QuestionLevel;

		return Question;
		break;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);

		Question.QuestionLevel = QuestionLevel;

		return Question;
		break;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);

		Question.QuestionLevel = QuestionLevel;

		return Question;
	}
	return Question;
   }

void GenerateQuizzQuestions(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
} 

int ReadQuestionAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n___________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else {
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
 		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-( \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz) {
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass) {
	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizzResults(stQuizz Quizz) {
	cout << "\n";      
	cout << "______________________________\n\n"; 
	cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);      
	cout << "\n______________________________\n\n"; 
	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;      
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;      
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;      
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;      
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;      
	cout << "______________________________\n";
}

void PlayMathGame() {
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

bool PlayAgain() {
	char PlayAgainc = 'y';
	cout << endl << "Do You Want To Play Again? Y/N? ";
	cin >> PlayAgainc;
	if (PlayAgainc == 'y' || PlayAgainc == 'Y') {
		ResetScreen();
		return true;
	}
	return false;
}

void StartGame() {
	do {
		PlayMathGame();
	} while (PlayAgain());
}

int main() {
	srand((unsigned)time(NULL));
	StartGame();
}















// My Solution
//#include <iostream>
//#include <Windows.h>
//
//using namespace std;
//
//enum enQuestionLevel{Easy = 1, Med = 2, Hard = 3, Mix = 4};
//enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mixed = 5};
//
//struct stQuestionInformation {
//    short QuestionNumber;
//    short FirstNumber;
//    string OperationTypeName;
//    short SecondNumber;
//    short Result;
//    int UserAnswer;
//    enQuestionLevel QuestionLevel;
//    enOperationType OperationType;
//};
//
//struct stQuiz {
//    short NumberOfQuestions;
//    enQuestionLevel QuestionLevel;
//    string QuestionLevelName;
//    enOperationType OperationType;
//    string OperationTypeName;
//    int NumberOfRightAnswers;
//    int NumberOfWrongAnswers;
//    string PassOrFail;
//};
//
//int RandomNumber(int From, int To) {
//    int RandomNum = rand() % (To - From + 1) + From;
//    return RandomNum;
//}
//
//void ResetGame() {
//    system("color 0F");
//    system("CLS");
//}
//
//bool PlayAgain() {
//    char PlayAgainc = 'y';
//    cout << "Do you Want To Play Again? Y/N?" << endl;
//    cin >> PlayAgainc;
//    if (PlayAgainc == 'y' || PlayAgainc == 'Y') {
//        return true;
//    }
//    return false;
//}
//
//int ReadHowManyQuestion() {
//    int QuestionNumber;
//    cout << "How Many Question Do You Want To Answer? ";
//    cin >> QuestionNumber;
//    
//    return QuestionNumber;
//}
//
//enQuestionLevel ReadQuestionLevel() {
//    int QuestionLevel;
//    do {
//    cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
//    cin >> QuestionLevel;
//    } while (QuestionLevel > 4 || QuestionLevel < 1);
//
//    switch (QuestionLevel) {
//    case 1:
//        return enQuestionLevel::Easy;
//        break;
//    case 2:
//        return enQuestionLevel::Med;
//        break;
//    case 3:
//        return enQuestionLevel::Hard;
//        break;
//    case 4:
//        return enQuestionLevel::Mix;
//        break;
//    }
//}
//
//enOperationType ReadOperationType() {
//    int OperationType;
//    do {
//        cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
//        cin >> OperationType;
//    } while (OperationType > 5 || OperationType < 1);
//
//    switch (OperationType) {
//    case 1:
//        return enOperationType::Add;
//        break;
//    case 2:
//        return enOperationType::Sub;
//        break;
//    case 3:
//        return enOperationType::Mul;
//        break;
//    case 4:
//        return enOperationType::Div;
//        break;
//    case 5:
//        return enOperationType::Mixed;
//        break;
//    }
//}
//
//string OperationName(enOperationType OperationType) {
//    switch (OperationType)
//    {
//    case enOperationType::Add:
//        return "+";
//        break;
//    case enOperationType::Sub:
//        return "-";
//        break;
//    case enOperationType::Mul:
//        return "*";
//        break;
//    case enOperationType::Div:
//        return "/";
//        break;
//    case enOperationType::Mixed:
//        return "Mix";
//        break;
//    }
//}
//
//string QuestionLevelName(enQuestionLevel QuestionLevel) {
//    switch (QuestionLevel) {
//    case Easy:
//        return "Easy";
//        break;
//    case Med:
//        return "Med";
//        break;
//    case Hard:
//        return "Hard";
//        break;
//    case Mix:
//        return "Mix";
//        break;
//    }
//}
//
//stQuiz FinalResult(int NumberOfRightQuestions, int NumberOfWrongQuestions) {
//    stQuiz PassOrFail;
//    if (NumberOfRightQuestions > NumberOfWrongQuestions)
//        PassOrFail.PassOrFail = "Pass";
//    else
//        PassOrFail.PassOrFail = "Fail";
//    return PassOrFail;
//}
//
//int GenerateNumbers(enQuestionLevel QuestionLevel) {
//    int GeneratedNumber;
//    switch (QuestionLevel) {
//    case Easy:
//        return RandomNumber(1, 9);
//        break;
//    case Med:
//        return RandomNumber(10, 30);
//        break;
//    case Hard:
//        return RandomNumber(70, 99);
//        break;
//    case Mix:
//        return RandomNumber(1, 100);
//        break;
//    }
//}
//
//stQuiz FillQuizInformation(int NumberOfRightAnswers, int NumberOfWrongAnswers, short NumberOfQusetions, enOperationType OperationType, enQuestionLevel QuestionLevel) {
//    stQuiz QuizInfo;
//    QuizInfo.NumberOfQuestions = NumberOfQusetions;
//    QuizInfo.NumberOfRightAnswers = NumberOfRightAnswers;
//    QuizInfo.NumberOfWrongAnswers = NumberOfWrongAnswers;
//    QuizInfo.OperationType = OperationType;
//    QuizInfo.OperationTypeName = OperationName(QuizInfo.OperationType);
//    QuizInfo.QuestionLevel = QuestionLevel;
//    QuizInfo.QuestionLevelName = QuestionLevelName(QuizInfo.QuestionLevel);
//
//    return QuizInfo;
//}
//
//void ShowPassOrFail(stQuiz Info) {
//    if (Info.NumberOfRightAnswers > Info.NumberOfWrongAnswers) {
//        cout << "Pass :-)";
//        system("color 2F");
//    }
//    else if (Info.NumberOfRightAnswers == Info.NumberOfWrongAnswers) {
//        cout << "Draw --";
//        system("color 6F");
//    }
//    else {
//        cout << "Fail :-(";
//        system("color 4F");
//    }
//}
//
//void ShowFinalQuizResluts(stQuiz QuizResults) {
//    cout << "\n___________________________________________________\n\n";
//    cout << "    Final Results is ";
//    ShowPassOrFail(QuizResults);
//    cout << "\n___________________________________________________\n\n";
//    cout << "Number Of Questions: " << QuizResults.NumberOfQuestions << endl;
//    cout << "Questions Level    : " << QuizResults.QuestionLevelName << endl;
//    cout << "Operation Type     : " << QuizResults.OperationTypeName << endl;
//    cout << "Number Of Right Answers: " << QuizResults.NumberOfRightAnswers << endl;
//    cout << "Number Of Wrong Answers: " << QuizResults.NumberOfWrongAnswers << endl;
//    cout << "\n___________________________________________________\n\n";
//}
//
//void QuestionForm(int FirstNumber, int SecondNumber, string OperationType) {
//    cout << FirstNumber << endl << SecondNumber << " " << OperationType << endl;
//    cout << "__________" << endl;
//}
//
//int CalculatAnswer(int FirstNumber, int SecondNumber, enOperationType OperationType) {
//    switch (OperationType) {
//    case Add:
//        return FirstNumber + SecondNumber;
//        break;
//    case Sub:
//        return FirstNumber - SecondNumber;
//        break;
//    case Mul:
//        return FirstNumber * SecondNumber;
//        break;
//    case Div:
//        return FirstNumber / SecondNumber;
//        break;
//    }
//}
//
//bool CheckAnswer(int UserAnswer, int RightAnswer) {
//    if (UserAnswer == RightAnswer) {
//        system("color 2F");
//        cout << "\nRight Answer :-)";
//        return true;
//    }
//    system("color 4F");
//    cout << "Wrong Answer :-(\n";
//
//    cout << "The Right Answer is: " << RightAnswer;
//    return false;
//}
//
//enOperationType MixedOperations() {
//    int Random = RandomNumber(1, 4);
//    switch (Random) {
//    case 1:
//        return enOperationType::Add;
//        break;
//    case 2:
//        return enOperationType::Sub;
//        break;
//    case 3:
//        return enOperationType::Mul;
//        break;
//    case 4:
//        return enOperationType::Div;
//        break;
//    }
//}
//
//stQuiz PlayQuiz(int HowManyQuestions) {
//    stQuestionInformation QuestionInfo;
//    int NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;
//    QuestionInfo.QuestionLevel = ReadQuestionLevel();
//    QuestionInfo.OperationType = ReadOperationType();
//
//    
//    if (QuestionInfo.OperationType == enOperationType::Mixed) {
//        for (int QuestionNumber = 1; QuestionNumber <= HowManyQuestions; QuestionNumber++) {
//            int UserAnswer;
//            enOperationType RoundOperation = MixedOperations();
//            cout << "\n\nQuestion [" << QuestionNumber << "/" << HowManyQuestions << "]\n\n";
//            QuestionInfo.OperationTypeName = OperationName(QuestionInfo.OperationType);
//            int FirstNumber = GenerateNumbers(QuestionInfo.QuestionLevel);
//            int SecondNumber = GenerateNumbers(QuestionInfo.QuestionLevel);
//            QuestionForm(FirstNumber, SecondNumber, OperationName(RoundOperation));
//            cin >> UserAnswer;
//            if (CheckAnswer(UserAnswer, CalculatAnswer(FirstNumber, SecondNumber, RoundOperation))) {
//                NumberOfRightAnswers++;
//            }
//            else {
//                NumberOfWrongAnswers++;
//            }
//        }
//    }
//    else {
//        for (int QuestionNumber = 1; QuestionNumber <= HowManyQuestions; QuestionNumber++) {
//            int UserAnswer;
//            cout << "\n\nQuestion [" << QuestionNumber << "/" << HowManyQuestions << "]\n\n";
//            QuestionInfo.OperationTypeName = OperationName(QuestionInfo.OperationType);
//            int FirstNumber = GenerateNumbers(QuestionInfo.QuestionLevel);
//            int SecondNumber = GenerateNumbers(QuestionInfo.QuestionLevel);
//            QuestionForm(FirstNumber, SecondNumber, QuestionInfo.OperationTypeName);
//            cin >> UserAnswer;
//            if (CheckAnswer(UserAnswer, CalculatAnswer(FirstNumber, SecondNumber, QuestionInfo.OperationType))) {
//                NumberOfRightAnswers++;
//            }
//            else {
//                NumberOfWrongAnswers++;
//            }
//        }
//    }
//    return FillQuizInformation(NumberOfRightAnswers, NumberOfWrongAnswers, HowManyQuestions, QuestionInfo.OperationType, QuestionInfo.QuestionLevel);
//}
//
//void StartQuiz() {
//    do {
//        ResetGame();
//        stQuiz Quiz = PlayQuiz(ReadHowManyQuestion());
//        ShowFinalQuizResluts(Quiz);
//    } while (PlayAgain());
//}
//
//int main() {
//
//    StartQuiz();
//}
