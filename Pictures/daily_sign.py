import numpy as np
import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates

significances=[16.53, 11.70, 7.45, 2.42, 6.71, 13.89, 12.40, 4.56,
               5.23, 2.43, 8.65, 5.42, 9.63, 6.26]
times=[1.90, 1.52, 1.01, 0.04, 1.99, 2.45, 2.64, 1.45, 0.75 , 0.33, 
       1.00, 2.06, 2.07, 0.69]

dates=["23/11/2019", "24/11/2019", "26/11/2019", "29/11/2019",
       "15/01/2020", "17/01/2020", "18/01/2020", "27/01/2020",
       "28/01/2020", "13/02/2020",
       "15/02/2020", "17/02/2020", "18/02/2020",
       "28/02/2020"]

x_values = [datetime.datetime.strptime(d,"%d/%m/%Y").date() for d in dates]
y_values= [i / np.sqrt(j) for i, j in zip(significances, times)] 

f, (ax, ax2, ax3) = plt.subplots(1, 3, facecolor='w')

formatter = mdates.DateFormatter("%Y-%m-%d")
ax.xaxis.set_major_formatter(formatter)
ax2.xaxis.set_major_formatter(formatter)
ax3.xaxis.set_major_formatter(formatter)

#locator = mdates.DayLocator()
#ax.xaxis.set_major_locator(locator)
#ax2.xaxis.set_major_locator(locator)
ax.set_xticks(x_values)
ax2.set_xticks(x_values)
ax3.set_xticks(x_values)


ax.plot(x_values, y_values, marker='.', linestyle='--', color='red', markerfacecolor='blue', markeredgecolor='blue')

ax2.plot(x_values, y_values, marker='.', linestyle='--', color='red', markerfacecolor='blue', markeredgecolor='blue')

ax3.plot(x_values, y_values, marker='.', linestyle='--', color='red', markerfacecolor='blue', markeredgecolor='blue')

ax.set_xlim(datetime.date(2019, 11, 22), datetime.date(2019, 11, 30))
ax2.set_xlim(datetime.date(2020, 1, 12), datetime.date(2020, 2, 3))
ax3.set_xlim(datetime.date(2020, 2, 12), datetime.date(2020, 2, 29))

ax.spines['right'].set_visible(False)
ax2.spines['left'].set_visible(False)
ax2.spines['right'].set_visible(False)
ax3.spines['left'].set_visible(False)
ax.tick_params(labelright='off')
ax2.tick_params(labelright='off')
ax3.tick_params(labelright=False)
#ax2.yaxis.tick_right()
ax2.yaxis.set_ticks([-1000])
ax.yaxis.tick_left()
ax3.yaxis.tick_right()

d = .015 # how big to make the diagonal lines in axes coordinates
# arguments to pass plot, just so we don't keep repeating them
kwargs = dict(transform=ax.transAxes, color='k', clip_on=False)
ax.plot((1-d,1+d), (-d,+d), **kwargs)
ax.plot((1-d,1+d),(1-d,1+d), **kwargs)

kwargs.update(transform=ax2.transAxes)  # switch to the bottom axes
ax2.plot((-d,+d), (1-d,1+d), **kwargs)
ax2.plot((-d,+d), (-d,+d), **kwargs)

ax2.plot((1-d,1+d), (-d,+d), **kwargs)
ax2.plot((1-d,1+d),(1-d,1+d), **kwargs)

kwargs.update(transform=ax3.transAxes)  # switch to the bottom axes
ax3.plot((-d,+d), (1-d,1+d), **kwargs)
ax3.plot((-d,+d), (-d,+d), **kwargs)

f.autofmt_xdate()
ax.tick_params(axis='x', rotation=70)
ax2.tick_params(axis='x', rotation=70)
ax3.tick_params(axis='x', rotation=70)
ax.set_ylabel(r"$\sigma / \sqrt{hour}$", size=20)

ax.axvspan(datetime.date(2019, 11, 23), datetime.date(2019, 11, 29), alpha=0.3, color='red')
ax2.axvspan(datetime.date(2020, 1, 15), datetime.date(2020, 2, 2), alpha=0.3, color='yellow')
ax3.axvspan(datetime.date(2020, 2, 13), datetime.date(2020, 2, 28), alpha=0.3, color='green')

ax.axhline(y=23.10/np.sqrt(4.5), color='red')
ax2.axhline(y=20.65/np.sqrt(11.3), color='orange')
ax3.axhline(y=15.48/np.sqrt(6.1), color='green')


f.savefig("daily_sigmas.pdf")
plt.show()
#Plot only total significance vs campaign

total_S = [23.10/np.sqrt(4.5), 20.65/np.sqrt(11.3), 15.48/np.sqrt(6.1)]
campaign=[1, 2, 3]
labels=['1st Crab Campaign', '2nd Crab Campaign', '3rd Crab Campaign']
plt.plot(campaign, total_S, marker='h', linestyle='--', linewidth=0.5, color='r')
plt.xticks(campaign, labels)
plt.ylabel(r"$\sigma / \sqrt{hour}$", size=20)
plt.savefig("total_S.pdf")
plt.show()


