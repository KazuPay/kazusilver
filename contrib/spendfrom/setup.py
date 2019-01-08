from distutils.core import setup
setup(name='KSLVspendfrom',
      version='1.0',
      description='Command-line utility for kazusilver "coin control"',
      author='Gavin Andresen',
      author_email='gavin@kazusilverfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
