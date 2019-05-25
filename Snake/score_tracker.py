import os

FILE_DIR = f"{os.getenv('APPDATA')}\Xoltia\Snake"
FILE_NAME = f"{FILE_DIR}\scores"

def get_scores():
    scores_file = open(FILE_NAME, 'r')
    scores = scores_file.readlines()
    scores_file.close()
    return list(map(int, [score.replace('\n', '') for score in scores]))
        
def save_score(score):
    if not os.path.exists(FILE_DIR):
        os.makedirs(FILE_DIR)
    scores_file = open(FILE_NAME, 'a+')
    scores_file.write(str(score) + '\n')
    scores_file.close()

def get_high_score():
    scores = get_scores()
    return max(scores)
