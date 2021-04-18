from datetime import (
    datetime,
)
from zipfile import (
    ZipFile,
)

import pandas  as pd
import pickle as pk


def question_rating_calc(
    tournament_name: dict,
    question_rating: list,
    dataset: dict,
) -> pd.DataFrame:

    tournament_rating = {}

    questions_count = 0
    for tournament in dataset:
        n_questions = len(dataset[tournament]['teams'][0]['mask'])
        start_index, end_index = questions_count, questions_count + n_questions
        tournament_rating[tournament] = question_rating[start_index: end_index].mean()
        questions_count += n_questions

    tournament_rating = sorted(tournament_rating.items(), key=lambda x: x[1])
    df_tournament_rating = pd.DataFrame(tournament_rating, columns=['id', 'rating']).drop(columns=['rating'])
    df_tournament_rating['name'] = df_tournament_rating['id'].apply(lambda x: tournament_name[x])
            
    return df_tournament_rating

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
) -> tuple:
    
    all_data = {}
    tournament_names = {}
    
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
        
        tournament_names[tournament_id] = dataset['tournaments'][tournament_id]['name']
            
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
    
    return all_data, dataset['players'], tournament_names

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