function p246
test_brute = 0;

fprintf('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n')
if ~test_brute
    g = 10^4;
    R = 1.5*10^4;
    a = sqrt(R^2-g^2)/2;
    b = 7500;
else
    a = 15;
    b = 18.445;
end;
if 0
    % testing code
    Px = 1;
    Py = 2;
    Qa = a^2/b^2*Px^2 + Py^2;
    Qb = -2*a^2*Px;
    Qc = b^2*(a^2-Py^2);

    xl = (-Qb-sqrt(Qb^2-4*Qa*Qc))/(2*Qa);
    slopel = (a/b*sqrt(b^2-xl^2) - Py)/(xl-Px);
     
    xr = (-Qb+sqrt(Qb^2-4*Qa*Qc))/(2*Qa);
    if Px > b,
        sloper = (-a/b*sqrt(b^2-xr^2) - Py)/(xr-Px);
    else
        sloper = (a/b*sqrt(b^2-xr^2) - Py)/(xr-Px);
    end;
    theta = find_angle(Px, Py, a, b)*180/pi
    
    figure(111); clf;
    x = linspace(-2*b, 2*b, 10000);
    xre = linspace(-b, b, 10000);
    
    plot(xre, a/b*sqrt(b^2-xre.^2), 'k', xre, -a/b*sqrt(b^2-xre.^2), 'k');
    hold all;
    if ~isinf(sloper)
        plot(x, slopel*(x-Px)+Py, x, sloper*(x-Px)+Py);
    else
        plot(x, slopel*(x-Px)+Py, [b b], [-a Py]);
    end;
    hold off;
    ylim([-2*a,2*a]);
    axis equal
else
% First compute number of points on vertical (top) axis
    Px = 0;
    
    if a == ceil(a)
        ymin = a + 1; 
    else
        ymin = ceil(a);
    end;
    Py = ymin;
        
    while find_angle(Px, Py, a, b) > pi/4,
        Py = Py + 1;
    end;
    Py = Py - 1;
    Nup = Py - ymin + 1;
    
    fprintf('Number on top: %g\n', Nup);

    % Now compute the number of points in the area between the top and
    % right axes
    Narea = 0;
    Px = 1;
    while(Py > 0)
        while find_angle(Px, Py, a, b) <= pi / 4 && Py > 0,
            Py = Py - 1;
        end;

        if Px > b,
            ymin = 0;
        else
            ymin = a/b*sqrt(b^2-Px^2);
            if ymin == floor(ymin)
                ymin = ymin;
            else
                ymin = floor(ymin);
            end;
        end;
        if Py > 0,
            Narea = Narea + Py - ymin;
        end;
        Px = Px + 1;
    end;
    Nright = Px - 2 - floor(b);
    fprintf('Number on right: %g\n', Nright);
    Ntotal = 4*Narea + 2*(Nup + Nright);
    fprintf('I count %.12g points in the up-right corner.\n', Narea + Nup + Nright);
    fprintf('I count %.12g points by being slick.\n', Ntotal);

%    note: find_angle doesn't work for (Px, Py) outside quadrant I
    if(test_brute)
        x = 0:(b+2*Nright);
        y = 0:(a+2*Nup);
        Nbrute = 0;
        for j = 1:length(x)
            xx = x(j);
            for k = 1:length(y)
                yy = y(k);
                if (find_angle(xx, yy, a, b) > pi/4) && (yy^2/a^2 + xx^2/b^2 > 1),
                    Nbrute = Nbrute + 1;
                end;
            end;
            if j == 1,
                fprintf('By brute force, %g on top.\n', Nbrute);
            end;
        end;

        fprintf('By brute force I find: %g in the up-right corner, inclusive\n', Nbrute);
    end;
    
end;
return;

function theta = find_angle(Px, Py, a, b);
    Qa = a^2/b^2*Px^2 + Py^2;
    Qb = -2*a^2*Px;
    Qc = b^2*(a^2-Py^2);

    xl = (-Qb-sqrt(Qb^2-4*Qa*Qc))/(2*Qa);
    slopel = (a/b*sqrt(b^2-xl^2) - Py)/(xl-Px);
     
    xr = (-Qb+sqrt(Qb^2-4*Qa*Qc))/(2*Qa);
    if Px > b,
        sloper = (-a/b*sqrt(b^2-xr^2) - Py)/(xr-Px);
        theta = atan(sloper)-atan(slopel);
    else
        sloper = (a/b*sqrt(b^2-xr^2) - Py)/(xr-Px);
        theta = pi-atan(-sloper)-atan(slopel);
    end;
return;

