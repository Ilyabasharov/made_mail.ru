from collections import (
    defaultdict,
)

def player2idx(
    dataset: dict,
    n_team: int,
) -> dict:
    
    player_n_team = player_per_team(dataset)
    
    clear_ids = set()
    for tournament in dataset:
        for team in dataset[tournament]['teams']:
            for player_id in team['players']:
                if player_n_team[player_id] > n_team:
                    clear_ids.add(player_id)
    
    player_to_idx = {player_id: idx for idx, player_id in enumerate(clear_ids)}
    idx_to_player = {idx: player_id for idx, player_id in enumerate(clear_ids)}
    
    return player_to_idx, idx_to_player

def questions_complexity(
    dataset: dict
) -> dict:
    
    #find the complexity of each questions in all tournaments
    
    question_stats = dict()
    
    for tournament in dataset:
        question_stats[tournament] = [[] for i in range(len(dataset[tournament]['teams'][0]['mask']))]
        for team in dataset[tournament]['teams']:
            for i, answer in enumerate(team['mask']):
                question_stats[tournament][i].append(answer)
    
    complexity = dict()
    
    for tournament in dataset:
        complexity[tournament] = [0]*len(question_stats[tournament])
        for i in range(len(question_stats[tournament])):
            answers = question_stats[tournament][i]
            complexity[tournament][i] = 1. - (sum(answers) / len(answers))
            
    return complexity


def player_per_team(
    dataset: dict,
) -> dict:
    
    players_id = defaultdict(set)
    
    for tournament_id in dataset:
        for team in dataset[tournament_id]['teams']:
            for player_id in team['players']:
                players_id[player_id].add(team['id'])
                
    distribution = {
        player_id: len(players_id[player_id])
        for player_id in players_id 
    }

    return distribution

def questions_per_tournament(
    dataset: dict,
) -> dict:

    distribution = {
        tournament_id: len(dataset[tournament_id]['teams'][0]['mask'])
        for tournament_id in dataset
    }
                
    return distribution

def percentage_correct_per_tournament(
    dataset: dict,
) -> dict:
    
    tournaments_ids = defaultdict(list)
    
    for tournament_id in dataset:
        for team in dataset[tournament_id]['teams']:
            tournaments_ids[tournament_id].append(
                sum(team['mask']) / len(team['mask'])
            )
            
    distribution = {
        id_: sum(tournaments_ids[id_]) / len(tournaments_ids[id_])
        for id_ in tournaments_ids
    }
    
    return distribution

def percentage_correct_per_team(
    dataset: dict,
) -> dict:
    
    team_ids = defaultdict(list)
    
    for tournament_id in dataset:
        for team in dataset[tournament_id]['teams']:
            team_ids[team['id']].append(
                sum(team['mask']) / len(team['mask'])
            )
            
    distribution = {
        id_: sum(team_ids[id_]) / len(team_ids[id_])
        for id_ in team_ids
    }
    
    return distribution