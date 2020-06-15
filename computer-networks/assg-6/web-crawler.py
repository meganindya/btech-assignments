# File: web-crawler.py

# Author: Anindya Kundu <anindya.k22@outlook.com>
# Date: 2020-06-15

# Reference: https://docs.python.org/3/library/
# Reference: https://dev.to/pranay749254/build-a-simple-python-web-crawler#:~:text=Python%20Web%20Crawler,are%20used%20%2D%20requests%20and%20BeautfulSoup4%20.

"""
A very simple web crawler.

Starts with a list of URLS (seeds), and parses each page for more links,
which it visits recursively. Collects the title, and other anchor text and
generates a dictionary of links for each keyword (title or anchor text).
Every visit includes links previously visited in descending order of
traversal.

Functions:

- `_crawlURL()`: craws URL provided
- `_crawl()`: craws URLs starting with seeds recursively (using BST algorithm)

How To Use This Module
======================
run this script using [python3 web-crawler.py]
"""


import requests
from bs4 import BeautifulSoup
from os import system


# max number of nexted URL visited (higher value, higher data, more time)
MAX_DEPTH = 0


def _crawlURL(url, parsed_urls, keydict):
    """
    Crawls passed URl. Parses the page looking for the title and anchor
    tags. Populates keyword lookup dictionary with the title and anchor
    text, and the hyperlinks.

    Parameters:

    - `url`: URL to parse
    - `parsed_urls`: previously parsed URLs
    - `keydict`: dictionary for keyword:URLs

    Returns:

    - list of hyperlinks found in the URL's page
    """


    # collect the markup of the page and convert in to soup readable type
    markup = requests.get(url).text
    soup = BeautifulSoup(markup, "html.parser")

    # fetch title of document and add it to dictionary
    title = soup.find("title").string.strip()
    if title in keydict:
        keydict[title].insert(0, url)
    else:
        keydict[title] = [url]
    keydict[title].extend(parsed_urls)

    # list of links in page
    links = []

    # fetch all anchor tags
    for anchor in soup.findAll('a'):
        # collect text from anchor
        text = anchor.string
        # collect hyperlink from anchor
        link = anchor.get('href')
        links.append(link)

        if type(text) is not type(None):
            text = text.strip()
        else:
            continue

        # add entry into dictionary as text:link
        if text in keydict:
            keydict[text].insert(0, link)
            keydict[text].insert(1, url)
        else:
            keydict[text] = [link, url]
        keydict[text].extend(parsed_urls)

    return links


def _crawl(seeds):
    """
    Parses the webpages recursively starting with seed URLs, and then visiting
    the URLs inside each URLs page, while generating a dictionary of URLs
    (pages) corresponding to each keyword (anchor text or URL page title).

    Parameters:

    - `seeds`: seed URLs

    Returns:

    - dictionary for keyword:URLs
    """


    if len(seeds) == 0:
        return

    # dictionary of keyword: URLs
    keydict = {}


    """
    Implement Breadth-First-Search (BFS) [to prevent huge call stacks and
    performance crash] to recursively parse the URLs
    """

    # queue of URLs
    queue = []

    # add all seed URLs to queue
    for seed in seeds:
        queue.append([0, [], seed])

    # loop until queue empty
    while len(queue) > 0:
        # extract from front
        entry = queue.pop()

        # depth of traversal
        depth = entry[0]
        if int(depth) > MAX_DEPTH:
            break
        # previously parsed URLs
        parsed_urls = entry[1]
        # current url to visit
        url = entry[2]

        # (crawl) parse current URL
        links = _crawlURL(url, parsed_urls, keydict)
        # add all links in curent URL's page to queue
        for link in links:
            p_urls = parsed_urls
            queue.append([depth + 1, p_urls.insert(0, url), link])

    return keydict


if __name__ == "__main__":
    """
    Attribute is __main__ when module is run as main program.
    """

    # clear console
    system('clear')

    # seed URLs
    seeds = []
    seeds.append("https://icmc2021.in")

    # crawl recursively starting from seeds
    keydict = _crawl(seeds)

    # print keyword dictionary
    for entry in keydict:
        if entry is None:
            continue

        print(entry + ":")
        links = keydict[entry]
        for link in links:
            print("  " + link)
        print("--------")
