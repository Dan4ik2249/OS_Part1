from typing import Union
from fastapi import FastAPI
import uvicorn
import baze_authors

app = FastAPI()
spisok_authors = {"Authors": ["Tolstoi", "Esenin"]}

@app.get("/")
def read_root():
    """Начальная страница"""
    authors = list(baze_authors.baze.keys())
    return {"Список авторов": authors}

@app.get("/{name}")
def func_works(name):
    works = list(baze_authors.baze[name].keys())
    return {"Список произведений": works}

@app.get("/{name}/{works_name}")
def hello2(name, works_name):
    works_name = baze_authors.baze[name][works_name]
    return works_name

if __name__ == "__main__":
    uvicorn.run(app)
