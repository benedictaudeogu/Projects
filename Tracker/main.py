#!/usr/bin/python3
# -*- coding: latin-1 -*-
import os
import pickle
import datetime
# Gmail API utils
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

# Request all access (permission to read/send/receive emails, manage the inbox, and more)
access = ['https://mail.google.com/']