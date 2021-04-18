from datetime import (
    datetime,
)
from zipfile import (
    ZipFile,
)

import pickle as pk


def read_dataset(
    path: str
) -> dict:
    
    dataset = {}

    with ZipFile(path) as zipfile:
        for subfile in zipfile.namelist():
            with zipfile.open(subfile) as file:
                dataset[subfile.split('.')[0]] = pk.load(file)
                
    return dataset

def preprocess(
    dataset: dict,
    from_time: datetime,
) -> dict:
    
    all_data = {}
    
    for tournament_id in dataset['tournaments']:
        
        if not dataset['results'][tournament_id]:
            continue
        
        tournament_time = datetime.fromisoformat(
            dataset['tournaments'][tournament_id]['dateStart']
        ).replace(tzinfo=None)
        
        if tournament_time < from_time:
            continue
        
        questions_length = set()
        
        for team in dataset['results'][tournament_id]:
            if team.get('mask', None) is not None:
                questions_length.add(len(team['mask']))
        
        if len(questions_length) != 1:
            continue
            
        tournament = {
            'time':  tournament_time,
            'teams': [],
        }
            
        for team in dataset['results'][tournament_id]:
            if team.get('mask', None) is None:
                continue
                
            tournament['teams'].append({
                'id':   team['team']['id'],
                'mask': list(map(int, team['mask'].replace('X', '0').replace('?', '0'))),
                'players': {
                    player['player']['id']
                    for player in team['teamMembers']
                }
            })
        
        if not tournament['teams']:
            continue
            
        all_data[tournament_id] = tournament
    
    return all_data, dataset['players']

def train_test_split(
    dataset: dict,
    train_time: datetime,
    test_time: datetime,
) -> tuple:
    
    train, test = dict(), dict()
    
    for tournament_id in dataset:
        if dataset[tournament_id]['time'] >= test_time:
            test[tournament_id] = dataset[tournament_id]
            
        else:
            train[tournament_id] = dataset[tournament_id]
            
    return train, test