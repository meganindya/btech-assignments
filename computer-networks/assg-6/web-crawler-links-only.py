# File: web-crawler-links-only.py

# Author: Anindya Kundu <anindya.k22@outlook.com>
# Date: 2020-06-19

# Reference: https://docs.python.org/3/library/
# Reference: https://dev.to/pranay749254/build-a-simple-python-web-crawler#:~:text=Python%20Web%20Crawler,are%20used%20%2D%20requests%20and%20BeautfulSoup4%20.

"""
A very simple web crawler.

Starts with a list of URLS (seeds), and parses each page for more links,
which it visits recursively. Makes a list of unique URLs.

Functions:

- `_crawlURL()`: craws URL provided
- `_crawl()`: craws URLs starting with seeds recursively (using BST algorithm)

How To Use This Module
======================
run this script using [python3 web-crawler-links-only.py]
"""


import requests
from bs4 import BeautifulSoup
from os import system


LIMIT = 10000   # number of links cut-off (minimum)
MAX_DEPTH = 5   # maximum nested link visits


"""
- private (in script) function `_crawlURL`
"""

def _crawlURL(url):
    """
    Crawls passed URl. Parses the page looking for the title and anchor tags.

    Parameters:

    - `url`: URL to parse

    Returns:

    - list of hyperlinks found in the URL's page
    """


    # exception handling for non-markup URLs
    try:
        markup = requests.get(url).text
        soup = BeautifulSoup(markup, "html.parser")
        
        # to store list of links in url's page
        links = []

        # fetch all anchor tags
        for anchor in soup.findAll('a'):
            # collect hyperlink from anchor and store 
            link = anchor.get('href')
            links.append(link)

        # `links` now contains all hyperlinks in url's page
        return links
    except:
        # return empty list for non-markup URLs
        return [];


"""
- private (in script) function `_crawl`
"""

def _crawl(seeds):
    """
    Parses the webpages recursively starting with seed URLs, and then visiting
    the URLs inside each URLs page, while generating a master list of all
    unique visited URLs except seed URLs.

    Parameters:

    - `seeds`: seed URLs

    Returns:

    - master links of all unique visited links (other than seeds)
    - number of PDF files found
    """
    

    # if no seeds        
    if len(seeds) == 0:
        return []
    
    """
    Implement Breadth-First-Search (BFS) [to prevent huge call stacks and
    performance crash] to recursively parse the URLs
    """

    # BFS queue
    queue = []

    # add all seed URLs to queue
    for seed in seeds:
        # push [depth, url]
        queue.append([0, seed])

    # to store master list of URLs and PDF count
    listout, pdf_count = [], 0

    # loop until queue is empty or cut-off limit reached
    while len(queue) > 0 and len(listout) <= LIMIT:
        # extract from front
        entry = queue.pop()

        # 1st element is depth
        depth = entry[0]
        # if maximum depth reached, skip link
        if depth == MAX_DEPTH:
            continue

        # 2nd element is url
        url = entry[1]

        # (crawl) parse current URL and fetch links within
        links = _crawlURL(url)

        # check each link before storing
        for link in links:
            # skip `NoneType` and empty links
            if link == None or link == "":
                continue

            # skip duplicate link
            if link not in queue:
                # print link if ends with ".pdf" (is a PDF file)
                if link[-4:] == ".pdf":
                    print(link)
                    pdf_count += 1

                # handle relative URLs
                if link[0] == "/":
                    if url[-1:] == "/":
                        link = url + link[0:]
                    else:
                        link = url + link

                # add to master list
                listout.append(link)
                # push to queue with incremented depth
                queue.append([depth + 1, link])

        # print length of master list after each iteration
        print(len(listout))

    # return master list
    return listout, pdf_count


"""
- Main program entry point
"""

if __name__ == "__main__":
    """
    Attribute is __main__ when module is run as main program.
    """

    # clear console
    system('clear')

    # seed URLs
    seeds = []
    seeds.append("https://mit.edu")

    # crawl recursively starting with seeds
    links, pdf_count = _crawl(seeds)

    print("\n{} PDF file/s found".format(pdf_count))

    # write the master list in a file
    f = open("links.txt", "w")
    for i, link in enumerate(links):
        if link != None or link != "":
            f.write(str(i) + ": " + link + "\n")
    f.close()
