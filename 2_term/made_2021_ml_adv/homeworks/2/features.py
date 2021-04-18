import numpy as np

from stats import (
    questions_complexity,
    player2idx,
)

from scipy import sparse

def team_answer_estimation(
    dataset: dict,
    player_to_idx: dict,
    prediction: list,
) -> list:

    count = 0
    result = []
    
    for tournament in dataset:
        for team in dataset[tournament]['teams']:
            for answer in team['mask']:
                per_team, n = [], 0
                for player in team['players']:
                    if player in player_to_idx:
                        per_team.append(prediction[count, 0])
                        count += 1
                        n += 1
                accum = 1. - np.prod(per_team)
                result.extend([accum]*n)
                
        
    return np.array(result) 

def create_test_prediction(
    dataset: dict,
    player_to_idx: dict,
    model,
    n_features: int,
) -> tuple:
    
    pred_per_tournament, gt_per_tournament = [], []
    
    for tournament in dataset:
        pred_per_team, gt_per_team = [], []
        for team in dataset[tournament]['teams']:
            player_idxs = [
                player_to_idx[player]
                for player in team['players']
                if player in player_to_idx
            ]
            
            if len(player_idxs) == 0:
                continue
                
            X = sparse.lil_matrix(
                arg1=(len(player_idxs), n_features),
                dtype=int,
            )
            X[range(len(player_idxs)), player_idxs] = 1

            pred_per_team.append(
                1. - model.predict_proba(X)[..., 0].prod()
            )

            gt_per_team.append(
                sum(team['mask']) / len(team['mask'])
            )
        
        pred_per_tournament.append(pred_per_team)
        gt_per_tournament.append(gt_per_team)
        
    return pred_per_tournament, gt_per_tournament

def create_train_matrix_baseline(
    dataset: dict,
    n_team:  int=3,
) -> tuple:
    
    player_to_idx, idx_to_player = player2idx(dataset, n_team)
    
    one_hot_players, one_hot_questions, complexity_feature, answers = [], [], [], []
    question_position = 0
    
    
    for tournament in dataset:
        n_questions = len(dataset[tournament]['teams'][0]['mask'])
        for team in dataset[tournament]['teams']:
            for i, answer in enumerate(team['mask']):
                for player in team['players']:
                    if player in player_to_idx:
                        one_hot_players.append(player_to_idx[player])
                        one_hot_questions.append(len(player_to_idx) + question_position + i)
                        answers.append(answer)
        
        question_position += n_questions
        
   
    questions = sparse.lil_matrix(
        arg1=(len(one_hot_players), len(player_to_idx) + question_position),
        dtype=int,
    )
    all_indexes = range(len(one_hot_players))
    questions[all_indexes, one_hot_players] = 1.
    questions[all_indexes, one_hot_questions] = 1.
    
    return questions, np.array(answers), player_to_idx
