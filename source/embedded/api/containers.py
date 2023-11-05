from controller.controller import Controller
from flask import Flask, Blueprint, request, Request, jsonify


def get_containers(controller: Controller):
    return jsonify({"Hello": "World"})
    
def change_containers(id: int, controller: Controller):
    return jsonify({"Hello": "World"})